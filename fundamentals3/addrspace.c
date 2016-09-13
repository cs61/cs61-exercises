#include <stdio.h>
#include <stdlib.h>

char global_ch = 'B';
const char const_global_ch = 'C';

int main(int argc, char* argv[]) {
    (void) argc, (void) argv;

    char local_ch = 'A';
    const char const_local_ch = 'E';
    char *heap_ch = (char*) malloc(1);
    *heap_ch = 'D';

    printf("Address of a global variable\t\t%p\n", &global_ch);
    printf("Address of a const global variable\t%p\n", &const_global_ch);
    printf("Address of a local variable\t\t%p\n", &local_ch);
    printf("Address of a const local variable\t%p\n", &const_local_ch);
    printf("Address of a heap variable\t\t%p\n", heap_ch);
    printf("Address of main\t\t\t\t%p\n", main);

    free(heap_ch);
    return 0;
}
