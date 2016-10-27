#ifndef WEENSYOS_PROCESS_H
#define WEENSYOS_PROCESS_H
#include "lib.h"
#include "x86-64.h"
#if WEENSYOS_KERNEL
#error "process.h should not be used by kernel code."
#endif

// process.h
//
//    Support code for WeensyOS processes.


// SYSTEM CALLS

// sys_getpid
//    Return current process ID.
static inline pid_t sys_getpid(void) {
    pid_t result;
    asm volatile ("int %1" : "=a" (result)
                  : "i" (INT_SYS_GETPID)
                  : "cc", "memory");
    return result;
}

// sys_yield
//    Yield control of the CPU to the kernel. The kernel will pick another
//    process to run, if possible.
static inline void sys_yield(void) {
    asm volatile ("int %0" : /* no result */
                  : "i" (INT_SYS_YIELD)
                  : "cc", "memory");
}

// sys_read
//    Read data from the RAMdisk at a given offset.
static inline ssize_t sys_read(void* buf, off_t off, size_t sz) {
    ssize_t result;
    // This is "GCC inline assembly"!
    asm volatile ("int %1" : "=a" (result)
                  : "i" (INT_SYS_READ),
                    "D" /* %rdi */ (buf),
                    "S" /* %rsi */ (off),
                    "d" /* %rdx */ (sz)
                    // A fourth argument would go in "c", for %rcx.
                    // Fifth and subsequent arguments would take more
                    // work---you'd need to use "local register variables."
                    // Or you could use "b" for %rbx, although that's not
                    // the normal x86-64 calling convention.
                  : "cc", "memory");
    return result;
}

// sys_panic(msg)
//    Panic.
static inline pid_t __attribute__((noreturn)) sys_panic(const char* msg) {
    asm volatile ("int %0" : /* no result */
                  : "i" (INT_SYS_PANIC), "D" (msg)
                  : "cc", "memory");
 loop: goto loop;
}


// OTHER HELPER FUNCTIONS

// app_printf(format, ...)
//    Calls console_printf() (see lib.h). The cursor position is read from
//    `cursorpos`, a shared variable defined by the kernel, and written back
//    into that variable. The initial color is based on the current process ID.
void app_printf(int colorid, const char* format, ...);

#endif
