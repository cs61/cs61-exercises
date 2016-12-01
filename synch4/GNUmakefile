SORT_PROGRAMS = $(sort $(patsubst %.c,%,$(wildcard sort-??.c)))
INCR_PROGRAMS = incr incrlock incrcmpxchg
PROGRAMS = $(SORT_PROGRAMS) $(INCR_PROGRAMS)
all: $(PROGRAMS)

O ?= 2
CFLAGS := -pthread
include ../common/rules.mk

%.o: %.c GNUmakefile $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

$(SORT_PROGRAMS): %: %.o linereader.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

$(INCR_PROGRAMS): %: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) -O0 -o $@ $<


clean:
	rm -f *.o *.core $(PROGRAMS)
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
