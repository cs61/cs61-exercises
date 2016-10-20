PROGRAMS = allocate allocatetouch allocaterandomtouch callocate \
	map maptouch maprandomtouch mapwrite \
	read readtouch readrandomtouch
all: $(PROGRAMS)

include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

$(PROGRAMS): %: %.o
	$(CC) $(CFLAGS) $(O) -o $@ $^ -lm

data: GNUmakefile
	yes 77777777777777777777777777777777777777777 | tr -d '\n' | head -c 1073741824 > data

flush-buffer-cache:
	sudo sh -c "sync; echo 1 > /proc/sys/vm/drop_caches"

clean:
	rm -f *.o $(PROGRAMS) data
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean clear-buffer-cache
