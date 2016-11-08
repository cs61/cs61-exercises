ALLPROG=parent child waiting-parent noisy-parent badchild waiting-parent2 waiting-parent3 util
all: $(ALLPROG)
O ?= -O2

include ../common/rules.mk

%: %.o $(BUILDSTAMP)
	$(CC) $(LDFLAGS) -o $@ $<

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

clean:
	rm -f $(ALLPROG) *.o
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
