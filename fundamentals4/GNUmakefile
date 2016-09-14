PROGRAMS = add addu fib membench-malloc membench-arena \
	membench-arena1 membench-arena2 membench-arena3 \
	membench-arena4

all: $(PROGRAMS)

DEFS += -pthread
include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

add: add.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

addu: addu.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

fib: fib.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

membench-%: membench.o mb-%.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

clean:
	rm -f $(PROGRAMS) *.o
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
