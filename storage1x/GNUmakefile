PROGRAMS = matrixmultiply
all: $(PROGRAMS)

include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

matrixmultiply: matrixmultiply.o
	$(CC) $(CFLAGS) $(O) -o $@ $^ -lm

clean:
	rm -f *.o $(PROGRAMS)
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
