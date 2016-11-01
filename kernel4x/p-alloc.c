#include "process.h"
#include "lib.h"

extern char end[];

void process_main(void) {
    app_printf(2, "[a=p-alloc, b=p-recurse, c=p-fork, d=p-panic]\n");
    app_printf(0, "Hello from p-alloc process %d\n", sys_getpid());

    char* data = ROUNDUP((char*) end, PAGESIZE); /* first heap page */
    int r = sys_page_alloc(data);
    app_printf(0, "sys_page_alloc returned %d\n", r);
    assert(r == 0);

    for (unsigned i = 0; i < PAGESIZE; ++i)
        data[i] = i;
    app_printf(0, "allocated memory is writable\n");

    for (unsigned i = 0; i < PAGESIZE; ++i)
        if (data[i] != (char) i)
            panic("bad memory at offset %d!", i);
    app_printf(0, "allocated memory is readable\n");

 spinloop: goto spinloop;
}
