PROGRAMS = $(patsubst mb-%.c,membench-%,$(wildcard mb-*.c))
ifeq ($(strip $(shell ld -ljemalloc 2>&1 | grep -- -ljemalloc)),)
PROGRAMS += membench-jemalloc
endif
ifneq ($(wildcard /usr/lib/libtcmalloc.so.4),)
PROGRAMS += membench-tcmalloc
endif
all: $(PROGRAMS)

DEFS += -pthread
include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

membench-%: membench.o mb-%.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

membench-jemalloc: membench.o mb-malloc.o
	$(CC) $(CFLAGS) $(O) -o $@ $^ -ljemalloc

membench-tcmalloc: membench.o mb-malloc.o
	$(CC) $(CFLAGS) $(O) -o $@ $^ /usr/lib/libtcmalloc.so.4

clean:
	rm -f *.o $(PROGRAMS) membench-jemalloc membench-tcmalloc
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
