// Data Representation examples

#include <stdio.h>
#include <stdlib.h>

union u {
    int intval;
    struct {
        short sval0, sval1;
    } sval;
    struct {
        char cval0, cval1, cval2, cval3;
    } cval;
};


int main(int argc, char* argv[]) {
    (void) argc, (void) argv;

    union u ud;
    ud.intval = 0xDEADBEEF;
    printf("As an integer: %x\n", ud.intval);
    printf("As two shorts: sval0=%hx sval1=%hx\n",
           ud.sval.sval0, ud.sval.sval1);
    printf("As four chars: cval0=%hhx cval1=%hhx cval2=%hhx cval3=%hhx\n",
           ud.cval.cval0, ud.cval.cval1, ud.cval.cval2, ud.cval.cval3);
    return 0;
}
