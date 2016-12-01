#include "linereader.h"

static void sort_lines(lineset* ls) {
    qsort(ls->lines, lineset_size(ls), sizeof(line), line_compare);
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        FILE* f = freopen(argv[1], "r", stdin);
        assert(f);
    }

    lineset* ls = read_lines(stdin);
    sort_lines(ls);

    // print the results
    for (line* l = ls->lines; l != ls->end_lines; ++l) {
        size_t nw = fwrite(l->s, 1, l->len, stdout);
        assert(nw == l->len);
    }

    return 0;
}
