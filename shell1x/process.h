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
    asm volatile ("int %1" : "=a" /* %rax */ (result)
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

// sys_pipewrite
//    Write data to pipe. Returns number of bytes written or -1 on error.
//    Should block if data cannot be written.
static inline ssize_t sys_pipewrite(const void* buf, size_t sz) {
    ssize_t result;
    asm volatile ("int %1" : "=a" /* %rax */ (result)
                  : "i" (INT_SYS_PIPEWRITE),
                    "D" /* %rdi */ (buf),
                    "S" /* %rsi */ (sz)
                  : "cc", "memory");
    return result;
}

// sys_piperead
//    Write data to pipe. Returns number of bytes written or -1 on error.
//    Should block if data cannot be written.
static inline ssize_t sys_piperead(void* buf, size_t sz) {
    ssize_t result;
    asm volatile ("int %1" : "=a" /* %rax */ (result)
                  : "i" (INT_SYS_PIPEREAD),
                    "D" /* %rdi */ (buf),
                    "S" /* %rsi */ (sz)
                  : "cc", "memory");
    return result;
}

// sys_panic(msg)
//    Panic.
static inline pid_t __attribute__((noreturn)) sys_panic(const char* msg) {
    asm volatile ("int %0" : /* no result */
                  : "i" (INT_SYS_PANIC), "D" /* %rdi */ (msg)
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
