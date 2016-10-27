#include "process.h"
#include "lib.h"

void process_main(void) {
    unsigned i = 0;
    while (1) {
        ++i;
        /*
        if (i % 8192 == 0) {
            char buf[30];
            off_t off = (rand() % 170) * 3;
            sys_write("61 ", off, 3);
        }
        */
        sys_yield();
    }
}
