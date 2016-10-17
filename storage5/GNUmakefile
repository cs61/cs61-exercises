PROGRAMS = stdio syscall mmap

all: $(PROGRAMS)

include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

%: %.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o $(PROGRAMS) *.out
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
