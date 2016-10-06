#include <stdio.h>

int main() {
    double answer = 0;

    answer += 100000000000;
    for (int i = 0; i < 100000; ++i)
        answer += 0.01;

    printf("%.12g (%a)\n", answer, answer);
}
