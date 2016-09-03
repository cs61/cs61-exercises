#include <stdio.h>

int add(int a, int b);
void allow_execute(const void* ptr, size_t size);
void hexdump_at(FILE* f, size_t first_offset, const void* ptr, size_t size);
