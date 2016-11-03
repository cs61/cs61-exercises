#include "helpers.h"

int main(int argc, char* argv[]) {
    assert(argc >= 2);

    pid_t p1 = fork();
    assert(p1 >= 0);

    FILE* f = fopen(argv[1], "w");

    const char* text;
    if (p1 == 0)
        text = "BABY\n";
    else
        text = "mama\n";

    for (int i = 0; i != 1000000; ++i)
        fputs(text, f);
}
