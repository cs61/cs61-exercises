// Data Representation examples; addresses of shorts

#include <stdio.h>
#include <stdlib.h>

int array[10];

int main(int argc, char* argv[]) {
    (void) argc, (void) argv;

    int* p = &array[0];

    printf("Address of array: %p\n", array);
    printf("Value of p: %p\n", p);
    printf("Value of &p[1]: %p\n", &p[1]);
    printf("Value of p + 1: %p\n", p + 1);
    return 0;
}
