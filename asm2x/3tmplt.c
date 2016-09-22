// FILL IN:
// STRUCT: Complete the struct declaration below, so that that when this file
// is compiled, it produces the assembly code found in file 3a.S and 3b.S
// FORMAT[123]: Use the correct printf format string to print out the
// relevant fields of the structure.
#include <stdio.h>
struct x {
	STRUCT
};

void output_func(struct x *arg1) {
	printf("FORMAT1\n", arg1->f1);
	printf("FORMAT2\n", arg1->f2);
	printf("FORMAT3\n", arg1->f3);
}
