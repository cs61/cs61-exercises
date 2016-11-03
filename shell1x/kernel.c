#include "kernel.h"
#include "lib.h"

// kernel.c
//
//    This is the kernel.


// INITIAL PHYSICAL MEMORY LAYOUT
//
//  +-------------- Base Memory --------------+
//  v                                         v
// +-----+--------------------+----------------+--------------------+---------/
// |     | Kernel      Kernel |       :    I/O | App 1        App 1 | App 2
// |     | Code + Data  Stack |  ...  : Memory | Code + Data  Stack | Code ...
// +-----+--------------------+----------------+--------------------+---------/
// 0  0x40000              0x80000 0xA0000 0x100000             0x140000
//                                             ^
//                                             | \___ PROC_SIZE ___/
//                                      PROC_START_ADDR

#define PROC_SIZE 0x40000

static proc processes[NPROC];   // array of process descriptors
                                // Note that `processes[0]` is never used.
proc* current;                  // pointer to currently executing proc

// memory representing a pipe buffer
static char pipebuffer[1];
// number of characters currently in pipe buffer
static size_t pipebuffer_len;

void schedule(void);
void run(proc* p) __attribute__((noreturn));


// kernel
//    Initialize the hardware and processes and start running.

void kernel(void) {
    hardware_init();
    console_clear();
    ticks = 0;
    timer_init(HZ);

    // Set up process descriptors
    memset(processes, 0, sizeof(processes));
    for (pid_t i = 0; i < NPROC; i++) {
        processes[i].p_pid = i;
        processes[i].p_state = P_FREE;
    }

    // Initialize pipe buffer
    pipebuffer_len = 0;

    for (pid_t i = 1; i <= 2; ++i) {
        // Load the process application code and data into memory,
        // set up its %eip and %esp, and mark it runnable.
        process_init(&processes[i], 0);
        int r = program_load(&processes[i], i - 1);
        assert(r >= 0);
        processes[i].p_registers.reg_rsp = PROC_START_ADDR + PROC_SIZE * i;
        processes[i].p_state = P_RUNNABLE;
    }

    // Protect kernel memory
    virtual_memory_map(kernel_pagetable, 0, 0, PROC_START_ADDR,
                       PTE_P | PTE_W, NULL);
    // (except for the console)
    virtual_memory_map(kernel_pagetable, (uintptr_t) console,
                       (uintptr_t) console, PAGESIZE,
                       PTE_P | PTE_W | PTE_U, NULL);
    lcr3((uintptr_t) kernel_pagetable);

    // Switch to the first process using run()
    run(&processes[1]);
}


// check_memory(pagetable, addr, sz, perm)
//    Check that every address in the range [`addr`, `addr` + `sz`)
//    is mapped in `pagetable` with *at least* permissions `perm`.
//    Returns 1 if the check succeeds, 0 if it fails.

int check_memory(x86_64_pagetable* pagetable, uintptr_t addr, size_t sz,
                 int perm) {
    while (sz > 0) {
        vamapping vam = virtual_memory_lookup(pagetable, addr);
        if ((vam.perm & perm) != perm)
            return 0;

        // This code walks through addresses one page at a time.
        // The code is written to avoid overflow errors.
        // To see why this is necessary, consider these two cases:
        // (1) addr == (uint64_t) -1, sz == 1
        //     (should check ONLY page at 0xFFFFFFFFFFFFF000)
        // (2) addr == (uint64_t) -1, sz == 2
        //     (should check pages at 0xFFFFFFFFFFFFF000 and 0)

        // address of next page to check; might wrap around to 0
        size_t next_page_addr = (addr + 0x1000) & ~0xFFF;

        // step from current addr to next page: always <= 0x1000
        size_t delta = next_page_addr - addr;

        // never take more than `sz` bytes
        if (delta > sz)
            delta = sz;

        sz -= delta;
        addr += delta;
    }
    return 1;
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
    // Copy the saved registers into the `current` process descriptor.
    current->p_registers = *reg;

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

    case INT_TIMER:
        ++ticks;
        schedule();
        break;  /* will not be reached */


    case INT_SYS_PIPEWRITE: {
        const char* buf = (const char*) current->p_registers.reg_rdi;
        size_t sz = current->p_registers.reg_rsi;

        if (!check_memory(kernel_pagetable, (uintptr_t) buf, sz,
                          PTE_P | PTE_U))
            // bad memory
            current->p_registers.reg_rax = -1;
        else if (sz == 0)
            // nothing to write
            current->p_registers.reg_rax = 0;
        else if (pipebuffer_len == 1)
            // no room, try again later
            current->p_registers.reg_rax = -1;
        else {
            // write 1 character
            pipebuffer[0] = buf[0];
            pipebuffer_len = 1;
            current->p_registers.reg_rax = 1;
        }

        break;
    }

    case INT_SYS_PIPEREAD: {
        char* buf = (char*) current->p_registers.reg_rdi;
        size_t sz = current->p_registers.reg_rsi;

        if (!check_memory(kernel_pagetable, (uintptr_t) buf, sz,
                          PTE_P | PTE_W | PTE_U))
            // bad memory
            current->p_registers.reg_rax = -1;
        else if (sz == 0)
            // empty read buffer
            current->p_registers.reg_rax = 0;
        else if (pipebuffer_len == 0)
            // nothing to read, try again later
            current->p_registers.reg_rax = -1;
        else {
            // read 1 character
            buf[0] = pipebuffer[0];
            pipebuffer_len = 0;
            current->p_registers.reg_rax = 1;
        }

        break;
    }


    case INT_GPF:
        error_printf(CPOS(23, 0), 0xC000, "Process %d GPF!\n", current->p_pid);
        current->p_state = P_BROKEN;
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
        current->p_state = P_BROKEN;
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

    // Load the process's current pagetable, which is `kernel_pagetable`.
    // Normally this is redundant, but it is necessary if the process's
    // page table changed (e.g., `virtual_memory_map` was called).
    lcr3((uintptr_t) kernel_pagetable);

    // This function is defined in k-exception.S. It restores the process's
    // registers then jumps back to user mode.
    exception_return(&p->p_registers);

 spinloop: goto spinloop;       // should never get here
}
