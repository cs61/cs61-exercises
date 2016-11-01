#include "kernel.h"
#include "lib.h"
#include "obj/k-binaries.h"

// kernel.c
//
//    This is the kernel.


// INITIAL PHYSICAL MEMORY LAYOUT
//
//  +-------------- Base Memory --------------+
//  v                                         v
// +-----+--------------------+----------------+------------------------------+
// |     | Kernel      Kernel |       :    I/O | Process              Process |
// |     | Code + Data  Stack |  ...  : Memory | Code + Data            Stack |
// +-----+--------------------+----------------+------------------------------+
// 0  0x40000              0x80000 0xA0000 0x100000                    0x300000
//                                             ^
//                                             | \________ PROC_SIZE ________/
//                                      PROC_START_ADDR

#define PROC_SIZE 0x200000

static proc processes[NPROC];   // array of process descriptors
                                // Note that `processes[0]` is never used.
proc* current;                  // pointer to currently executing proc

#define HZ 100                  // timer interrupt frequency (interrupts/sec)
static unsigned ticks;          // # timer interrupts so far

void schedule(void);
void run(proc* p) __attribute__((noreturn));

static uint32_t page_refcount[NPAGES];

static void pageinfo_init(void);
int pagetable_alloc(proc* p);
int pagetable_copy(proc* dst, proc* src);
static void fork(void);


// kernel
//    Initialize the hardware and processes and start running.

void kernel(const char* command) {
    hardware_init();
    pageinfo_init();
    console_clear();
    timer_init(HZ);
    if (testmalloc())
	panic("Malloc test failed");

    // Set up process descriptors
    memset(processes, 0, sizeof(processes));
    for (pid_t i = 0; i < NPROC; i++) {
        processes[i].p_pid = i;
        processes[i].p_state = P_FREE;
    }

    // Load the process application code and data into memory,
    // set up its %eip and %esp, and mark it runnable.
    int program_number = 0;
    if (command && strlen(command) == 1 && command[0] >= 'a'
        && command[0] < ('a' + WEENSYOS_NBINARIES))
        program_number = command[0] - 'a';

    pagetable_alloc(&processes[1]);
    process_init(&processes[1], 0);
    int r = program_load(&processes[1], program_number, NULL);
    assert(r >= 0);
    processes[1].p_registers.reg_rsp = PROC_START_ADDR + PROC_SIZE;
    uintptr_t stack = page_alloc_unused();
    virtual_memory_map(processes[1].p_pagetable,
                       processes[1].p_registers.reg_rsp - PAGESIZE,
                       stack, PAGESIZE,
                       PTE_P | PTE_W | PTE_U, NULL);
    processes[1].p_state = P_RUNNABLE;

    // Switch to the first process using run()
    run(&processes[1]);
}


// page_alloc_unused
//    Allocate an unused physical page, increment its reference count, and
//    return its physical address (which is also its virtual address in the
//    kernel_pagetable). Returns NULL on failure.

uintptr_t page_alloc_unused(void) {
    for (int pn = 0; pn < NPAGES; ++pn)
        if (page_refcount[pn] == 0) {
            ++page_refcount[pn];
            return PAGEADDRESS(pn);
        }
    return 0;
}

// page_unalloc
void page_unalloc(uintptr_t addr) {
    int pn = PAGENUMBER(addr);
    assert(page_refcount[pn] == 1);
    page_refcount[pn] = 0;
}


// pagetable_alloc
//    Create a safe page table and install it in `p->p_pagetable`.

int pagetable_alloc(proc* p) {
    // Initialize empty page table
    x86_64_pagetable* pages[5];
    for (int i = 0; i < 5; ++i) {
        pages[i] = (x86_64_pagetable*) page_alloc_unused();
        assert(pages[i]);
        memset(pages[0], 0, PAGESIZE);
    }
    pages[0]->entry[0] = (x86_64_pageentry_t) pages[1] | PTE_P | PTE_W | PTE_U;
    pages[1]->entry[0] = (x86_64_pageentry_t) pages[2] | PTE_P | PTE_W | PTE_U;
    pages[2]->entry[0] = (x86_64_pageentry_t) pages[3] | PTE_P | PTE_W | PTE_U;
    pages[2]->entry[1] = (x86_64_pageentry_t) pages[4] | PTE_P | PTE_W | PTE_U;

    // All memory is kernel-accessible; the console is user-accessible
    virtual_memory_map(pages[0], 0, 0, MEMSIZE_PHYSICAL, PTE_P|PTE_W, NULL);
    virtual_memory_map(pages[0],
                       (uintptr_t) console, (uintptr_t) console, PAGESIZE,
                       PTE_P|PTE_W|PTE_U, NULL);

    p->p_pagetable = pages[0];
    return 0;
}


// exception(reg)
//    Exception handler (for interrupts, traps, and faults).
//
//    The register values from exception time are stored in `reg`.
//    The processor responds to an exception by saving application state on
//    the kernel's stack, then jumping to kernel assembly code (in
//    k-exception.S). That code saves more registers on the kernel's stack,
//    then calls exception().
//
//    Note that hardware interrupts are disabled whenever the kernel is running.

void exception(x86_64_registers* reg) {
    // Copy the saved registers into the `current` process descriptor
    // and always use the kernel's page table.
    current->p_registers = *reg;
    lcr3((uintptr_t) kernel_pagetable);

    // It can be useful to log events using `log_printf`.
    // Events logged this way are stored in the host's `log.txt` file.
    /*log_printf("proc %d: exception %d\n", current->p_pid, reg->reg_intno);*/

    // Show the current cursor location.
    console_show_cursor(cursorpos);

    // If Control-C was typed, exit the virtual machine.
    check_keyboard();


    // Actually handle the exception.
    switch (reg->reg_intno) {

    case INT_SYS_PANIC:
        panic("%s", (const char*) reg->reg_rdi);
        break;  /* will not be reached */

    case INT_SYS_GETPID:
        current->p_registers.reg_rax = current->p_pid;
        break;

    case INT_SYS_YIELD:
        schedule();
        break;  /* will not be reached */

    case INT_SYS_PAGE_ALLOC: {
        uintptr_t wantva = (uintptr_t) current->p_registers.reg_rdi;
        uintptr_t page = page_alloc_unused();
        if (page) {
            virtual_memory_map(current->p_pagetable,
                               wantva, page, PAGESIZE,
                               PTE_P | PTE_W | PTE_U, NULL);
            current->p_registers.reg_rax = 0;
        } else
            current->p_registers.reg_rax = -1;
        break;
    }

    case INT_SYS_FORK:
        fork();
        break;

    case INT_TIMER:
        ++ticks;
        schedule();

    case INT_GPF:
        error_printf(CPOS(23, 0), 0xC000, "Process %d GPF!\n", current->p_pid);
        current->p_state = P_BLOCKED;
        break;

    case INT_PAGEFAULT: {
        uintptr_t addr = rcr2();
        const char* operation = reg->reg_err & PFERR_WRITE
                ? "write" : "read";
        const char* problem = reg->reg_err & PFERR_PRESENT
                ? "protection problem" : "missing page";
        char name[20];
        if (reg->reg_err & PFERR_USER)
            snprintf(name, sizeof(name), "Process %d", current->p_pid);
        else
            strcpy(name, "Kernel");

        error_printf(CPOS(23, 0), 0xC000,
                     "%s page fault for %p (%s %s, rip=%p)!\n",
                     name, addr, operation, problem, reg->reg_rip);
        if (!(reg->reg_err & PFERR_USER))
            panic("Kernel page fault");
        current->p_state = P_BLOCKED;
        break;
    }

    default:
        panic("Unexpected exception %d!\n", reg->reg_intno);
        break;                  /* will not be reached */

    }


    // Return to the current process (or run something else).
    if (current->p_state == P_RUNNABLE)
        run(current);
    else
        schedule();
}


// fork
//    Copy the current process!

static void fork(void) {
    lcr3((uintptr_t) kernel_pagetable);
    assert(processes[2].p_state == P_FREE);
    panic("fork not implemented yet!");
}


// schedule
//    Pick the next process to run and then run it.
//    If there are no runnable processes, spins forever.

void schedule(void) {
    pid_t pid = current->p_pid;
    while (1) {
        pid = (pid + 1) % NPROC;
        if (processes[pid].p_state == P_RUNNABLE)
            run(&processes[pid]);
        // If Control-C was typed, exit the virtual machine.
        check_keyboard();
    }
}


// run(p)
//    Run process `p`. This means reloading all the registers from
//    `p->p_registers` using the `popal`, `popl`, and `iret` instructions.
//
//    As a side effect, sets `current = p`.

void run(proc* p) {
    assert(p->p_state == P_RUNNABLE);
    current = p;

    // Load the process's current pagetable
    lcr3((uintptr_t) p->p_pagetable);

    // This function is defined in k-exception.S. It restores the process's
    // registers then jumps back to user mode.
    exception_return(&p->p_registers);

 spinloop: goto spinloop;       // should never get here
}


// pageinfo_init
//    Initialize the `pageinfo[]` array.

void pageinfo_init(void) {
    extern char end[];

    for (uintptr_t addr = 0; addr < MEMSIZE_PHYSICAL; addr += PAGESIZE) {
        int refcount = 0;
        if (physical_memory_isreserved(addr)
            || (addr >= KERNEL_START_ADDR && addr < (uintptr_t) end)
            || addr == KERNEL_STACK_TOP - PAGESIZE)
            refcount = 1;
        page_refcount[PAGENUMBER(addr)] = refcount;
    }
}
