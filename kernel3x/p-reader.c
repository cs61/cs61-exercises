#include "process.h"
#include "lib.h"

void process_main(void) {
    unsigned i = 0;
    while (1) {
        ++i;
        if (i % 8192 == 0) {
            char buf[30];
            off_t off = rand() % 512;
            ssize_t r = sys_read(buf, off, 16);
            app_printf(0, "read    @%04zx+%zu: \"%.*s\"\n", off, r,
                       (int) r, buf);
        }
        sys_yield();
    }
}
