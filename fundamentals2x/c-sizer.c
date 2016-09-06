#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

/// spec_size(spec)
///    Return the size of the C struct specified by `spec`, as compiled on
///    an x86-64 machine. `spec` is a string of characters where each character
///    corresponds to a struct member of some fundamental type. Specifically:
///
///         `c`    char (or signed char, unsigned char)
///         `s`    short (or unsigned short)
///         `i`    int (or unsigned int)
///         `l`    long (or unsigned long)
///         `f`    float
///         `d`    double
///         `p`    pointer
///
///    Thus, `spec_size("c")` should return 1, since `sizeof(char) == 1`.
///    `spec_size("cic")` should return 12, since
///    `sizeof(struct { char a; int b; char c; }) == 12`.
///
///    Your function may return 0 if `spec` is invalid (or it may crash, or
///    do anything else).
///
///    ADVANCED FEATURES! Implement one or more of these if you have time.
///    (1) Support arrays: `"c20"` is an array of 20 chars.
///    (2) Support nested structs: `"{ci}"` is a nested struct containing
///        a char and an int. Note that `spec_size("cci")` should differ
///        from `spec_size("c{ci}")`; why?
///    (3) Support arrays of nested structs: `"{ci}20"` is an array of 20
///        `{ci}`s.
///    (4) Support unions: `"<ci>"` is a union of a char and an int;
///        `spec_size("<ci>")` should equal 4.
///
///    You should implement this function using computer arithmetic and your
///    knowledge of C data representation. You can test your knowledge using
///    the C compiler. However, it is also instructive to *implement* this
///    function using the C compiler. The function could generate a C
///    file that prints the size of the specified struct, then compile that
///    file, run the resulting executable, and parse and return the result!
///    Try `man system` and `man popen`.

size_t spec_size(const char* spec) {
    (void) spec;
    // YOUR CODE HERE
    return 0;
}

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i)
        printf("%8zu %s\n", spec_size(argv[i]), argv[i]);
}
