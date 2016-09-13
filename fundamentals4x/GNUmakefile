PROGRAMS = $(patsubst mb-%.c,membench-%,$(wildcard mb-*.c))
all: $(PROGRAMS)

DEFS += -pthread
include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

membench-%: membench.o mb-%.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

clean:
	rm -f *.o $(PROGRAMS)
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
