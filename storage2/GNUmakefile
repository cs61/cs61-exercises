PROGRAMS = w01_sync w02_syscall w03_stdio

all: $(PROGRAMS)

include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

%: %.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o $(ALLPROGRAMS) data
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
