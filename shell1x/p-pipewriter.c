#include "process.h"
#include "lib.h"

const char* messages[] = {
    "Hello, friend!\n",
    "I am a plumber.\n",
    "I'm talking through a pipe.\n"
};
    
void process_main(void) {
    size_t nwrites = 0;

    while (1) {
        // First, write a message.
        const char* message = messages[rand() % arraysize(messages)];
        size_t pos = 0;
        size_t len = strlen(message);
        while (pos < len) {
            ++nwrites;
            ssize_t w = sys_pipewrite(&message[pos], len - pos);
            if (w == 0)
                panic("pipe closed for writing!\n");
            else if (w > 0)
                pos += w;
        }

        // Print that message was written.
        app_printf(0, "%zu syscalls: wrote %s", nwrites, message);

        // Wait 1-3 seconds.
        unsigned long wait_until = ticks + HZ + (rand() % (2 * HZ));
        while (ticks < wait_until)
            sys_yield();
    }
}
