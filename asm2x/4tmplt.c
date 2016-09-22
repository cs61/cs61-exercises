// FILL IN:
// UNION: Complete the union declaration below, so that that when this file
// is compiled, it produces the assembly code found in file 4a.S and 4b.S
// FORMAT[123]: Use the correct printf format string to print out the
// relevant fields of the structure.
#include <stdio.h>
union x {
	UNION
};

void output_func(struct x *arg1) {
	printf("FORMAT1\n", arg1->u1);
	printf("FORMAT2\n", arg1->u2);
	printf("FORMAT3\n", arg1->u3);
}
