#include "helpers.h"

int main(void) {
    pid_t p1 = fork();
    assert(p1 >= 0);

    const char* text;
    if (p1 == 0)
        text = "BABY\n";
    else
        text = "mother\n";

    for (int i = 0; i != 1000000; ++i)
        fputs(text, stdout);
}
