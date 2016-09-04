// Data Representation examples

#include <stdio.h>
#include <stdlib.h>

union data {
	int intval;
	struct {
		short sval1, sval2;
	} sval;
	struct {
		char cval1, cval2, cval3, cval4;
	} cval;
};


int main(int argc, char *argv[]) {
	union data ud = { 0xDEADBEEF };

	(void)argc;
	(void)argv;
	printf("As an integer: %x\n", ud.intval);
	printf("As two shorts: sval1=%hx sval2=%hx\n",
	    ud.sval.sval1, ud.sval.sval2);
	printf("As four chars: cval1=%hhx cval2=%hhx cval3=%hhx cval4=%hhx\n",
	    ud.cval.cval1, ud.cval.cval2, ud.cval.cval3,ud.cval.cval4);

	return 0;
}
