#include "process.h"
#include "lib.h"

unsigned f_helper(unsigned i);

unsigned f(unsigned i) {
    if (i == 0)
        return i;
    else
        return f_helper(i) + i;
}

unsigned f_helper(unsigned i) {
    return f(i - 1);
}


void process_main(void) {
    app_printf(0, "Hello from p-recurse process %d\n", sys_getpid());
    for (unsigned i = 0; i < 1000; ++i)
        app_printf(0, "f(%u) == %u\n", i, f(i));
 spinloop: goto spinloop;
}
