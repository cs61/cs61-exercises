PROGRAMS = waitdemo waitlimit-poll waitlimit-block waitlimit-block2 \
	waitlimit-block3 waitlimit-block4 waitlimit-block5 \
	infinikill
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
