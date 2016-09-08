// Data Representation examples

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[22];
    unsigned int age;
    char house[15];
} student;

student array_of_students[10];
int main(int argc, char* argv[]) {
    student eddie = { "Eddie", 29, "Maxwell Dworkin" };

    (void) argc, (void) argv;

    array_of_students[5] = eddie;
    printf("Where is the array? %p\n", array_of_students);
    printf("Where is Eddie? %p\n", &eddie);
    printf("How large is a struct student???\n");
    return 0;
}
