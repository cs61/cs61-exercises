PROGRAMS = pingpong pingpong-mutex pingpong-cv
all: $(PROGRAMS)

O ?= 2
include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

$(PROGRAMS): %: %.o
	$(CC) $(CFLAGS) -pthread $(O) -o $@ $^


check: pingpong
	./pingpong | awk -f check.awk

check-cv: pingpong-cv
	./pingpong-cv | awk -f check.awk
	
check-mutex: pingpong-mutex
	./pingpong-mutex | awk -f check.awk

clean:
	rm -f *.o *.core $(PROGRAMS)
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
