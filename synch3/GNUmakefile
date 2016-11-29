SERVER_PROGRAMS = $(sort $(patsubst %.c,%,$(wildcard serviceserver-??.c)))
SORT_PROGRAMS = $(sort $(patsubst %.c,%,$(wildcard sort-??.c)))
SERVICE_PROGRAMS = serviceblaster serviceclient servicelookup serviceserver \
	$(SERVER_PROGRAMS)
PROGRAMS = $(SERVICE_PROGRAMS) $(SORT_PROGRAMS)
all: $(PROGRAMS)

O ?= 2
CFLAGS := -pthread
include ../common/rules.mk

%.o: %.c GNUmakefile $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

$(SERVICE_PROGRAMS): %: %.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

$(SORT_PROGRAMS): %: %.o linereader.o
	$(CC) $(CFLAGS) $(O) -o $@ $^


clean:
	rm -f *.o *.core $(PROGRAMS)
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
