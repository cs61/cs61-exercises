#include "linereader.h"

static lineset* parse_lines(char* buf, size_t size) {
    lineset* ls = (lineset*) malloc(sizeof(lineset));
    assert(ls);

    // create array of strings
    size_t lines_cap = 1024;
    size_t lines_size = 0;
    line* lines = (line*) malloc(lines_cap * sizeof(line));
    for (size_t pos = 0; pos != size; ) {
        size_t start = pos;
        while (pos != size && buf[pos] != '\n')
            ++pos;
        if (pos != size)
            ++pos;

        if (lines_size == lines_cap) {
            lines_cap *= 2;
            lines = (line*) realloc(lines, lines_cap * sizeof(line));
        }
        lines[lines_size].s = &buf[start];
        lines[lines_size].len = pos - start;
        ++lines_size;
    }

    // return lineset
    ls->lines = lines;
    ls->end_lines = lines + lines_size;
    ls->capacity = lines_cap;
    ls->spare = NULL;
    ls->buffer = buf;
    ls->buffer_size = size;
    return ls;
}

lineset* read_lines(FILE* f) {
    // find size of file
    struct stat s;
    int r = fstat(fileno(f), &s);
    assert(r >= 0 && S_ISREG(s.st_mode));
    size_t filesize = s.st_size;

    // read file into memory
    char* filebuf = malloc(filesize);
    assert(filebuf);
    size_t nread = fread(filebuf, 1, filesize, f);
    assert(nread == filesize);

    return parse_lines(filebuf, filesize);
}

void scramble_lines(lineset* ls) {
    (void) ls;
}







lineset* mmap_lines(FILE* f) {
    // find size of file
    struct stat s;
    int r = fstat(fileno(f), &s);
    assert(r >= 0 && S_ISREG(s.st_mode));
    size_t filesize = s.st_size;

    // read file into memory
    char* filebuf = mmap(NULL, filesize, PROT_READ, MAP_SHARED,
                         fileno(f), 0);
    assert(filebuf != MAP_FAILED);

    return parse_lines(filebuf, filesize);
}
