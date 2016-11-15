PROGRAMS = waitlimit-signalfd waitlimit-pselect
all: $(PROGRAMS)

O ?= 2
include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

$(PROGRAMS): %: %.o
	$(CC) $(CFLAGS) $(O) -o $@ $^


clean:
	rm -f *.o *.core $(PROGRAMS)
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
