SERVER_PROGRAMS = $(sort $(patsubst %.c,%,$(wildcard serviceserver-??.c)))
PROGRAMS = serviceblaster serviceclient servicelookup serviceserver $(SERVER_PROGRAMS)
all: $(PROGRAMS)

O ?= 2
CFLAGS := -pthread
include ../common/rules.mk

%.o: %.c GNUmakefile $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

$(PROGRAMS): %: %.o
	$(CC) $(CFLAGS) $(O) -o $@ $^


clean:
	rm -f *.o *.core $(PROGRAMS)
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
