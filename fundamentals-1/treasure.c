#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#define arraysize(a) (sizeof(a) / sizeof(*a))

const char* strings[] = {
    /*  0 */ "\336\255\276\357",
    /*  1 */ "XR.U.BOYVRZNETBFRYGMREANFVQADVBRJWXQBNZF",
    /*  2 */ "curl -L http://bit.ly/2bxeOkl",
    /*  3 */ "  ENGVB  ",
    /*  4 */ "\xEB\xFE",
    /*  5 */ /* The following string is 681 bytes long: */
             "GIF89aZ\x00Z\x00\xf2\x00\x00\x04\x04\x04"
             "\xfc\xf4\x04\xec\x1c\x3c\xfc\xdc\xdc\xfc\x2c\x94\xf8\xf4\xf8\xfc"
             "\xfc\xfc\xff\xff\xff\x21\xf9\x04\x09\x14\x00\x07\x00\x2c\x00\x00"
             "\x00\x00\x5a\x00\x5a\x00\x00\x03\xff\x78\xba\xdc\xfe\x30\xca\x49"
             "\xab\xbd\x38\xeb\xcd\xbb\xff\x60\x28\x8e\x64\x69\x9e\x68\xaa\xae"
             "\x6c\xeb\xbe\x70\x2c\xcf\x74\x6d\xdf\x78\xae\xef\x3c\x08\xfc\xbd"
             "\x14\x20\x10\x20\x00\x82\xa6\x21\x91\x60\x44\x8e\x00\x84\x25\xb3"
             "\xe9\xfc\x40\xa7\xd8\xa3\xe2\xc7\xd5\xda\xba\xde\xcb\x15\x3b\xe5"
             "\x1a\xce\xe8\xb0\x0c\x80\x3e\x73\x2d\x63\x72\x94\xdd\x4e\xd7\xe8"
             "\x75\x77\x18\xdc\x9d\x4a\x99\x44\x78\x75\x6a\x2f\x82\x79\x06\x5d"
             "\x87\x88\x80\x44\x45\x7e\x86\x76\x6b\x8a\x93\x79\x43\x8c\x7f\x4c"
             "\x90\x88\x7c\x84\x27\x9a\x94\x95\x8e\x51\xa2\x65\x3f\x69\x4a\x72"
             "\x40\x2a\x9f\xa0\x6d\x71\x72\x46\xa5\xaf\x64\x01\x9d\x24\xac\xad"
             "\x6e\xb0\x65\x8c\xb1\xbb\xa3\xb6\x4f\xb9\xa0\x5c\x58\x4b\x50\x8d"
             "\xb5\xb4\xa2\x81\x2b\xb8\xc3\x57\x9c\xc8\x8d\x71\xc9\x65\x2d\xcf"
             "\xad\xd5\x8e\x3f\xbd\xdb\x7f\xc1\xb7\xc3\x93\x63\xc9\x74\x63\xa8"
             "\x7e\xa4\xe1\xc2\xe3\x8a\x57\x81\x82\xc5\xe9\xa9\xd8\xee\xe4\x99"
             "\x9f\x50\xf4\x64\xec\x22\xd9\xd0\x70\x59\x9a\x95\xc9\xde\xbd\x83"
             "\x69\x8e\x19\x2b\xe2\x2f\x04\x40\x84\x87\xd2\xc1\x6b\x66\x10\xe2"
             "\x3d\x4b\xbc\x28\xb2\x78\x68\xb1\xff\x52\x3f\x55\x15\x3b\xba\x8b"
             "\x73\xae\x90\x48\x84\x43\x4c\xb9\x31\x79\xf2\x22\x9b\x02\x7a\xc0"
             "\xac\xa2\xa4\xb2\x65\x44\x36\x0d\x3b\x48\xab\x19\x93\x23\x39\x00"
             "\x30\xdf\xb1\xbc\xc9\x13\xa5\x19\xa1\x2e\x58\x25\xea\xb8\x34\xe2"
             "\xd0\x4a\x47\xdf\x15\x1d\x14\xf5\xd4\x1b\x7b\x55\xf5\xd0\xa4\xf6"
             "\x73\xaa\x1d\x90\x28\xb2\x8e\xe4\xfa\x33\xa8\x53\x67\x5a\x34\x0d"
             "\x58\x3b\x80\x98\xd7\x71\x39\xc5\x6d\x32\xc0\x96\xed\xc9\xba\x56"
             "\x11\xad\xa9\x59\x77\xad\xc8\xbe\x6d\x5d\xc5\xfd\x77\x44\x10\xde"
             "\xbf\x7d\x5d\x6d\x19\xec\x61\x8f\xcd\x3c\x87\x57\x32\x60\xbc\x81"
             "\x90\x4f\xa6\x34\xae\x2e\x7e\x7c\x13\x07\xd8\xb7\x4c\x29\xaf\x6a"
             "\xd0\xd4\x28\xd8\x1d\xb6\x76\xaa\xd6\x5c\x25\xb5\xba\x5a\xc5\x5e"
             "\x8b\xce\x4c\x3a\xb6\x11\x79\x0b\x67\xd3\x3e\xf0\x43\x80\x6f\x01"
             "\xfb\x22\xf6\xab\xf2\x80\xcb\xef\xdf\x6f\x67\xe9\x86\xd1\xfb\xb8"
             "\x6f\xd0\x8b\x86\x13\xe7\xed\x1c\xb9\x36\x39\xb5\x88\x03\xa8\x6e"
             "\x9d\x26\xac\xec\xad\x05\xc0\xac\xfe\x8c\xe0\x1c\x27\xdb\x05\x9c"
             "\xe1\xae\x74\x61\x16\xf4\xdc\x8f\xb7\xbf\xb4\x0e\x49\x7a\x03\xf1"
             "\xf5\x2d\xc4\x44\x85\x47\xfa\xf8\x6e\xc0\x09\xb7\x0c\x2c\xcb\x85"
             "\x05\xe0\x73\x82\xfd\xb2\x4b\x81\x49\x1c\xf8\x9c\x6d\x0a\x8e\x72"
             "\x4d\x0f\xff\x39\xf8\x0a\x7f\xa3\x48\xc1\xa0\x27\x16\x62\x44\xdf"
             "\x32\xf1\x84\x97\x5f\x23\xfb\x91\x92\xcf\x86\x68\x39\xd7\xcd\x2e"
             "\x98\xb0\x36\xdd\x62\x6f\x6c\xb2\x9a\x4a\x28\x32\x87\x86\x59\x34"
             "\x29\xf6\x22\x69\x17\xe9\xb8\xe3\x02\x97\xe1\x51\x63\x0c\x1c\x09"
             "\xf9\x23\x04\xd0\xc9\xe8\xe2\x91\xb5\xed\xc4\xe4\x93\x50\x46\x29"
             "\xe5\x94\x54\x56\x39\x43\x02\x00\x3b",
    /*  6 */ "true",
    /*  7 */ "echo Hello, world",
    /*  8 */ "false"
};
const size_t nstrings = arraysize(strings);

const float floats[] = {
    /*  0 */ 1.48024688796e+29,
    /*  1 */ 0.0 / 0.0,
    /*  2 */ 1 / 2.0,
    /*  3 */ -1 / 2.0,
    /*  4 */ 6.02e23,
    /*  5 */ 299792458,
    /*  6 */ -1.18024688796e+29,
    /*  7 */ 0xDEADBEEF
};
const size_t nfloats = arraysize(floats);

const int ints[] = {
    /*  0 */ 0,
    /*  1 */ -2147483648,
    /*  2 */ 1114898432,
    /*  3 */ 1920,
    /*  4 */ 259649728,
    /*  5 */ 282984512,
    /*  6 */ 301596736,
    /*  7 */ 522125344,
    /*  8 */ 534773776,
    /*  9 */ 260046856,
    /* 10 */ 134218254,
    /* 11 */ 134218504,
    /* 12 */ 140509208,
    /* 13 */ 207732764,
    /* 14 */ 234881120,
    /* 15 */ 58721152,
    /* 16 */ 16776952,
    /* 17 */ 18751240,
    /* 18 */ 59766536,
    /* 19 */ 209518584,
    /* 20 */ 135265796,
    /* 21 */ 134739970,
    /* 22 */ 134739972,
    /* 23 */ 101062668,
    /* 24 */ 33032176,
    /* 25 */ 128142,
    /* 26 */ 128169,
    /* 27 */ 65,
    /* 28 */ 128568
};
const size_t nints = arraysize(ints);

typedef int (*treasure_function)(int argc, char* argv[]);
static const treasure_function treasure_functions[];
const size_t nfunctions = 21;


/// usage()
///    Print a usage message and exit the program.

static void usage(void) {
    fprintf(stderr, "Usage: ./treasure TREASURENUMBER [ARG1 ARG2...]\n\
    The ARGs depend on the TREASURENUMBER. Good luck!\n");
    exit(1);
}



/* ARGUMENT PARSING FUNCTIONS */

/// string_argument(argno, argc, argv)
///    Return the string argument at position `argno` in the argument list
///    defined by `argc` and `argv`. Exit the program with a usage message
///    if there is no such argument (`argno >= argc`).

const char* string_argument(int argno, int argc, char* argv[]) {
    if (argno >= argc) {
        fprintf(stderr, "Missing argument ARG%d.\n", argno + 1);
        usage();
    }
    return argv[argno];
}


/// long_argument_named(argno, argc, argv, argname)
///    Return the integer argument at position `argno` in the argument list.
///    Exit with a usage message for argument name `argname` on failure (no
///    such argument, or argument can't be parsed as an integer).

long long_argument_named(int argno, int argc, char* argv[],
                         const char* argname) {
    if (argno >= argc || argv[argno][0] == '\0') {
        fprintf(stderr, "Missing argument %s.\n", argname);
        usage();
    }
    char* endptr;
    long l = strtol(argv[argno], &endptr, 0);
    if (*endptr != '\0') {
        fprintf(stderr, "Argument %s should be a number.\n", argname);
        usage();
    }
    return l;
}


/// long_argument(argno, argc, argv)
///    Return the integer argument at position `argno` in the argument list.
///    Exit with a usage message on failure.

long long_argument(int argno, int argc, char* argv[]) {
    char buf[10];
    sprintf(buf, "ARG%d", argno + 1);
    return long_argument_named(argno, argc, argv, buf);
}


/// size_argument(argno, argc, argv)
///    Return the `size_t` argument at position `argno` in the argument list.
///    Exit with a usage message on failure.

size_t size_argument(int argno, int argc, char* argv[]) {
    if (argno >= argc || argv[argno][0] == '\0') {
        fprintf(stderr, "Missing argument ARG%d.\n", argno + 1);
        usage();
    }
    char* endptr;
    long l = strtol(argv[argno], &endptr, 0);
    if (*endptr != '\0' || l < 0) {
        fprintf(stderr, "Argument ARG%d should be an unsigned number.\n", argno + 1);
        usage();
    }
    return (size_t) l;
}


/// index_argument(argno, argc, argv, limit)
///    Return the `size_t` argument at position `argno` in the argument list.
///    Exit with a usage message on failure (no such argument, argument not
///    an integer, or argument `>= limit`).

size_t index_argument(int argno, int argc, char* argv[], size_t limit) {
    size_t s = size_argument(argno, argc, argv);
    if (s >= limit) {
        fprintf(stderr, "Argument ARG%d out of bounds (limit %zu).\n", argno + 1, limit);
        usage();
    }
    return s;
}


/// float_argument(argno, argc, argv)
///    Return the real-valued argument at position `argno` in the argument
///    list. Exit with a usage message on failure.

double float_argument(int argno, int argc, char* argv[]) {
    if (argno >= argc || argv[argno][0] == '\0') {
        fprintf(stderr, "Missing argument ARG%d.\n", argno + 1);
        usage();
    }
    char* endptr;
    double d = strtod(argv[argno], &endptr);
    if (*endptr != '\0') {
        fprintf(stderr, "Argument ARG%d should be a real number.\n", argno + 1);
        usage();
    }
    return d;
}



/* PRINTING FUNCTIONS */

/// print_hexdump(data, len)
///    Print to stdout a `hexdump -C`-style dump of the `len` bytes of memory
///    starting at `data`.

void print_hexdump(const void* data, size_t len) {
    const unsigned char* s = (const unsigned char*) data;
    for (size_t j = 0; j < len; j += 16) {
        for (size_t i = j; i < j + 16; ++i) {
            if (i && i % 4 == 0)
                printf(" ");
            if (i < len)
                printf("%02X", s[i]);
            else
                printf("  ");
        }
        printf("  |");
        for (size_t i = j; i < j + 16 && i < len; ++i)
            if (s[i] >= ' ' && s[i] < 127)
                printf("%c", s[i]);
            else
                printf(".");
        printf("|\n");
    }
}


/// print_rot13(s, len)
///    Print to stdout the first `len` bytes of string `s`, with uppercase
///    letters translated by ROT13.

void print_rot13(const char* s, size_t len) {
    for (size_t i = 0; i < len; ++i)
        if (isupper((unsigned char) s[i]))
            printf("%c", 'A' + (s[i] - 'A' + 13) % 26);
        else
            printf("%c", s[i]);
}


/// print_utf8_char(ch)
///    Print to stdout the UTF-8 encoding of Unicode character `ch`.
///    See https://en.wikipedia.org/wiki/UTF-8 for more.

void print_utf8_char(int ch) {
    assert(ch > 0 && ch <= 0x10FFFF);
    char buf[5];
    char* s = buf;
    if (ch <= 127)
        *s++ = ch;
    else if (ch <= 0x7FF) {
        *s++ = 0xC0 | (ch >> 6);
        goto last6bits;
    } else if (ch <= 0xFFFF) {
        *s++ = 0xE0 | (ch >> 12);
        goto last12bits;
    } else {
        *s++ = 0xF0 | (ch >> 18);
        *s++ = 0x80 | ((ch >> 12) & 0x3F);
    last12bits:
        *s++ = 0x80 | ((ch >> 6) & 0x3F);
    last6bits:
        *s++ = 0x80 | (ch & 0x3F);
    }
    *s++ = 0;
    printf("%s", buf);
}



/* TREASURE FUNCTIONS */

int treasure0(int argc, char* argv[]) {
    (void) argc, (void) argv;
    print_hexdump(strings[0], 4);
    return 0;
}

int treasure1(int argc, char* argv[]) {
    size_t stringno = index_argument(0, argc, argv, nstrings);
    printf("%s", strings[stringno]);
    return 0;
}

int treasure2(int argc, char* argv[]) {
    size_t stringno = index_argument(0, argc, argv, nstrings);
    size_t len = size_argument(1, argc, argv);
    fwrite(strings[stringno], 1, len, stdout);
    return 0;
}

int treasure3(int argc, char* argv[]) {
    size_t functionno = index_argument(0, argc, argv, nfunctions);
    const unsigned char* function_data =
        (const unsigned char*) treasure_functions[functionno];
    size_t offset = size_argument(1, argc, argv);
    size_t nbytes = size_argument(2, argc, argv);
    print_hexdump(&function_data[offset], nbytes);
    return 0;
}

int treasure4(int argc, char* argv[]) {
    size_t stringno = index_argument(0, argc, argv, nstrings);
    return system(strings[stringno]);
}

int treasure5(int argc, char* argv[]) {
    printf("%d", argc);
    for (int i = 0; i < argc; ++i)
        printf("%s", argv[i]);
    printf("\n");
    return 0;
}

int treasure6(int argc, char* argv[]) {
    printf("6");
    for (int i = 0; i < argc; ++i)
        printf("%s", argv[i]);
    printf("\n");
    return 0;
}

int treasure7(int argc, char* argv[]) {
    size_t stringno = index_argument(0, argc, argv, nstrings);
    int (*function)(int, char*[]) = (int (*)(int, char*[])) strings[stringno];
    return function(argc, argv);
}

int treasure8(int argc, char* argv[]) {
    size_t stringno = index_argument(0, argc, argv, nstrings);
    const char* string_to_print = strings[stringno];

    long first = 0, nchars = strlen(string_to_print);
    if (argc >= 2) {
        first = long_argument(1, argc, argv);
        nchars -= first;
    }
    if (argc >= 3)
        nchars = long_argument(2, argc, argv);
    if (first < 0 || nchars < 0)
        usage();

    print_rot13(&string_to_print[first], nchars);
    printf("\n");
    return 0;
}

int treasure9(int argc, char* argv[]) {
    long a = long_argument(0, argc, argv);
    long b = long_argument(1, argc, argv);
    while (b != 0) {
        long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int treasure10(int argc, char* argv[]) {
    int n = long_argument(0, argc, argv);
    if (n <= 0)
        usage();
    int sum = 0, i = 0;
    while (sum < n) {
        sum += i;
        i = (i + 1) % n;
    }
    return sum;
}

int treasure11(int argc, char* argv[]) {
    size_t floatno = index_argument(0, argc, argv, nfloats);
    printf("%f\n", floats[floatno]);
    return 0;
}

int treasure12(int argc, char* argv[]) {
    size_t floatno = index_argument(0, argc, argv, nfloats);
    print_hexdump(&floats[floatno], sizeof(float));
    return 0;
}

int treasure13(int argc, char* argv[]) {
    double a = float_argument(0, argc, argv);
    printf("%f\n", (1 + sqrt(a)) / 2);
    return 0;
}

int treasure14(int argc, char* argv[]) {
    long unicode = long_argument(0, argc, argv);
    if (unicode <= 0 || unicode > 0x10FFFF)
        usage();
    // print the UTF-8 encoding of the specified character.
    // Try `./treasure 14 65`!
    // Try `./treasure 14 0xA7` (U+00A7)!
    // Try `./treasure 14 167`!
    print_utf8_char(unicode);
    printf("\n");
    return 0;
}

int treasure15(int argc, char* argv[]) {
    (void) argc, (void) argv;
    return 4022250974U;
}

int treasure16(int argc, char* argv[]) {
    size_t pos = index_argument(0, argc, argv, nints);
    size_t count = size_argument(1, argc, argv);
    if (pos + count > nints)
        usage();
    for (size_t i = 0; i < count; ++i) {
        unsigned val = ints[pos + i];
        while (val != 0) {
            printf("%c", val & 1 ? '*' : ' ');
            val >>= 1;
        }
        printf("\n");
    }
    return 0;
}

int treasure17(int argc, char* argv[]) {
    size_t stringno = index_argument(0, argc, argv, nstrings);
    const char* s = strings[stringno];
    long len = strlen(s);
    long first_pos = 0, increment = 1, count = len;
    if (argc > 1)
        first_pos = long_argument(1, argc, argv);
    if (argc > 2)
        increment = long_argument(2, argc, argv);
    if (argc > 3)
        count = long_argument(3, argc, argv);
    if (first_pos < 0 || increment <= 0) {
        fprintf(stderr, "ARGs out of range\n");
        usage();
    }
    for (long i = 0; i != count && first_pos < len; ++i, first_pos += increment)
        printf("%c", s[first_pos]);
    printf("\n");
    return 0;
}

int treasure18(int argc, char* argv[]) {
    size_t stringno = index_argument(0, argc, argv, nstrings);
    long color_argument = long_argument(1, argc, argv);
    if (color_argument < 0 || color_argument >= 16)
        usage();
    // ANSI escape codes for colorful goodness!
    printf("\x1B[30;48;5;%ldm", color_argument);
    print_rot13(strings[stringno], strlen(strings[stringno]));
    printf("\x1B[0m\n");
    return 0;
}

int treasure19(int argc, char* argv[]) {
    size_t intno = index_argument(0, argc, argv, nints);
    float f;
    memcpy(&f, &ints[intno], sizeof(float));
    printf("%f\n", f);
    return 0;
}

int treasure20(int argc, char* argv[]) {
    size_t floatno = index_argument(1, argc, argv, nfloats);
    printf("%f\n", float_argument(0, argc, argv) * floats[floatno]);
    return 0;
}

int treasure21(int argc, char* argv[]) {
    size_t intno = index_argument(0, argc, argv, nints);
    print_utf8_char(ints[intno]);
    printf("\n");
    return 0;
}


static const treasure_function treasure_functions[] = {
    treasure0,
    treasure1,
    treasure2,
    treasure3,
    treasure4,
    treasure5,
    treasure6,
    treasure7,
    treasure8,
    treasure9,
    treasure10,
    treasure11,
    treasure12,
    treasure13,
    treasure14,
    treasure15,
    treasure16,
    treasure17,
    treasure18,
    treasure19,
    treasure20,
    treasure21,
    NULL
};

int main(int argc, char* argv[]) {
    long treasure_number = long_argument_named(1, argc, argv, "TREASURENUMBER");
    int result = treasure_functions[treasure_number](argc - 2, &argv[2]);
    if (result != 0)
        printf("%d\n", result);
    exit(0);
}
