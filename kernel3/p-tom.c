#include "process.h"
#include "lib.h"

void process_main(void) {
    unsigned i = 0;

    while (1) {
        ++i;
        if (i % 1024 == 0)
            app_printf(0, "Hi, I'm Tom! #%x\n", i);
        if (i % 4096 == 0) {
            app_printf(0, "AVADA KEDAVRA!\n");
            // Get pointer to code for kernel's sys_getpid() handler
            uint8_t* code_ptr = (uint8_t*) 0x40042;
            // Replace that handler with an infinite loop
            code_ptr[0] = 0xeb;
            code_ptr[1] = 0xfe;
            // Invoke the handler: kernel will infinite-loop with
            // interrupts disabled!
            (void) sys_getpid();
        }
        sys_yield();
    }
}
