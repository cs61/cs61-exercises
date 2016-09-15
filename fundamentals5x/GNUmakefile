PROGRAMS = nogcbench gcbench
all: $(PROGRAMS)

# More garbage gets cleaned up more reliably when optimization is off.
O ?= 0

include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

nogcbench: nogcbench.o m61gc.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

gcbench: gcbench.o m61gc.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

clean:
	rm -f *.o $(PROGRAMS) gcbench-sol
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
