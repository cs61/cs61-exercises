#include "process.h"
#include "lib.h"

void process_main(void) {
    unsigned i = 0;

    while (1) {
        ++i;
        if (i % 1024 == 0)
            app_printf(1, "Hi, I'm Ginny! #%x\n", i);
        sys_yield();
    }
}
