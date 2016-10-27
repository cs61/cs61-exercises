#include "process.h"
#include "lib.h"

void process_main(void) {
    /*
    extern char end[];
    char* map = ROUNDUP((char*) end, PAGESIZE)
        + (read_cycle_counter() % 8) * PAGESIZE;

    {
        // Order of arguments: address, size, prot, offset
        char* result = sys_mmap(map, 0x1000, PROT_READ, 0);
        if (map != result)
            panic("mmap failure!");
    }

    unsigned i = 0;
    while (1) {
        ++i;
        if (i % 8192 == 0) {
            off_t off = rand() % 512;
            app_printf(1, "mapread @%04zx+%u: \"%.*s\"\n", off, 16U,
                       16, &map[off]);
        }
        sys_yield();
    }
    */

    while (1)
        sys_yield();
}
