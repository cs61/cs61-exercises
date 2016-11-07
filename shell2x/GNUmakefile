all: babysh
O ?= -O2

include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

babysh: babysh.o
	$(CC) $(CFLAGS) $(O) -o $@ $^ -lm

clean:
	rm -f babysh *.o
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
