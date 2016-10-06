PROGRAMS = noncommutative $(sort $(patsubst %.c,%,$(wildcard r[0-9]*.c)))
all: $(PROGRAMS) data

include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

noncommutative: noncommutative.o
	$(CC) $(CFLAGS) $(O) -o $@ $^ -lm

r%: r%.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

data:
	yes 77777777777777777777777777777777777777777 | tr -d '\n' | head -c 51200000 > data

clean:
	rm -f *.o $(PROGRAMS) data
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
