PROGRAMS = spy61
all: $(PROGRAMS)

O ?= 2
include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) -pthread $(DEPCFLAGS) $(O) -o $@ -c $<

$(PROGRAMS): %: %.o
	$(CC) $(CFLAGS) -pthread $(O) -o $@ $^

clean:
	rm -f *.o *.core $(PROGRAMS)
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
