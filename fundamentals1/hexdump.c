#include <stdio.h>

void hexdump_at(FILE* f, size_t first_offset, const void* ptr, size_t size) {
    const unsigned char* p = (const unsigned char*) ptr;
    fprintf(f, "%08zx", first_offset);
    for (size_t i = 0; i != size; ++i) {
        if (i && i % 16 == 0)
            fprintf(f, "\n%08zx", first_offset + i);
        fprintf(f, "%s%02x", (i % 8 == 0 ? "  " : " "), (unsigned) p[i]);
    }
    fprintf(f, "\n");
}
