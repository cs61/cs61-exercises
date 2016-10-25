#include "process.h"
#include "lib.h"

void process_main(void) {
    unsigned i = 0;

    while (1) {
        ++i;
        if (i % 1024 == 0)
            app_printf(0, "Hi, I'm Tom! #%x\n", i);
        sys_yield();
    }
}
