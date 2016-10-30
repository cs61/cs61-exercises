#include "process.h"
#include "lib.h"

void process_main(void) {
    pid_t parent = sys_getpid();
    pid_t p = sys_fork();
    app_printf(sys_getpid(), "Hello from process %d, fork returned %d\n",
               sys_getpid(), p);
    for (unsigned i = 0; i < 10; ++i) {
        app_printf(sys_getpid(), "%d\n", i);
        sys_yield();
    }
 spinloop: goto spinloop;
}
