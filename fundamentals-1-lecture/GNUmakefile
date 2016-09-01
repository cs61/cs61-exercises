PROGRAMS = add addin
PROGRAMS += numset-list numset-vector
PROGRAMS += numset-file numset-basiclist numset-array
PROGRAMS += numset-tree numset-bsearchvector

all: $(PROGRAMS)

ALLPROGRAMS = $(PROGRAMS)

include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

add: add.o addf.o hexdump.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

addin: addin.o hexdump.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

numset-%: numset.o %.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(ALLPROGRAMS) *.o
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
