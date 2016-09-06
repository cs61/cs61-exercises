all: c-sizer

include ../common/rules.mk

# This “pattern rule” tells `make` how to build any `.o` file from the `.c`
# file with the same name. For instance, it will build `c-sizer.o` from
# `c-sizer.c`, `foo.o` from `foo.c`, and so on. You can type `make c-sizer.o`
# (or any other `.o`) to invoke this rule directly.
%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

# This rule tells `make` how to build the `c-sizer` program from the `c-sizer.o`
# object. The first line says that before running the recipe for `c-sizer`,
# `make` should build `c-sizer.o` (which will use the pattern rule above).
# The second line is the recipe. The special `$@` variable expands to the
# rule’s target, which, here, is `c-sizer`. The special `$^` variable expands
# to the rule’s dependencies, which, here, is `c-sizer.o`. (If you added more
# dependencies, they would also show up.) So this rule says that to build
# `c-sizer`, first build `c-sizer.o`, then run
# `gcc -W -Wall -O3 -o c-sizer c-sizer.o` (the exact command will depend on
# the $(CC), $(CFLAGS), and $(O) variables).
c-sizer: c-sizer.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

c-sizer-sol: c-sizer-sol.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

clean:
	rm -f *.o c-sizer c-sizer-sol
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
