#include "process.h"
#include "lib.h"

void process_main(void) {
    char buf[200];
    size_t buflen = 0;
    size_t nreads = 0;

    while (1) {
        // Read a message
        while (memchr(buf, '\n', buflen) == NULL) {
            ++nreads;
            ssize_t r = sys_piperead(&buf[buflen], sizeof(buf) - buflen);
            if (r == 0)
                panic("pipe closed for reading!\n");
            else if (r > 0)
                buflen += r;
        }

        // Print the message that was read
        char* newline = (char*) memchr(buf, '\n', buflen);
        size_t messagelen = (newline + 1) - buf;
        app_printf(1, "%zu syscalls: read %.*s", nreads, messagelen, buf);

        // Shift down rest of buffer
        memmove(buf, &buf[messagelen], buflen - messagelen);
        buflen -= messagelen;
    }
}
