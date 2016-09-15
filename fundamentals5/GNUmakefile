PROGRAMS = fib nogcbench gcbench
all: $(PROGRAMS)

O ?= 0
include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

fib: fib.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

nogcbench: nogcbench.o m61gc.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

gcbench: gcbench.o m61gc.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

clean:
	rm -f $(PROGRAMS) *.o
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
