all: treasure
O ?= -O0

include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

treasure: treasure.o
	$(CC) $(CFLAGS) $(O) -o $@ $^ -lm

clean:
	rm -f treasure *.o
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
