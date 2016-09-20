ASMS := $(patsubst %.c,%.s,$(wildcard *.c))
ASM_OBJECTS := $(patsubst %.s,%.o,$(ASMS))
ASM_PROGRAMS := $(shell grep -l main $(wildcard *.[cs]) | sed 's,\.[cs],,' | sort -u)
DEFAULT_ASM_CFLAGS = -O1
DEFAULT_ASM_CFLAGS_DEBUG = -g $(DEFAULT_ASM_CFLAGS)

PROGRAMS = $(ASM_PROGRAMS)

all: $(ASMS) $(PROGRAMS)

ALLPROGRAMS = $(PROGRAMS)
PREFER_GCC ?= 1

include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(call run,$(CC) $(CFLAGS) -O1 $(DEPCFLAGS) -o $@ -c,COMPILE,$<)

$(ASM_OBJECTS): %.o: %.s $(BUILDSTAMP)
	$(call run,$(CC) -o $@ -c,ASSEMBLE,$<)

%.noopt.o: %.c $(BUILDSTAMP)
	$(call run,$(CC) $(CFLAGS) -O0 $(DEPCFLAGS) -o $@ -c,COMPILE -O0,$<)

%.prof.o: %.c $(BUILDSTAMP)
	$(call run,$(CC) $(CFLAGS) -pg -O1 $(DEPCFLAGS) -o $@ -c,COMPILE -pg,$<)


%.s: %.c GNUmakefile
	@ARGS=$$(grep '^//!' $< | sed 's/.*! *//'); \
	  CFLAGS="`echo "$(CFLAGS)" | sed 's/ *-g */ /'`"; \
	  if test -z "$$ARGS"; then ARGS="$(DEFAULT_ASM_CFLAGS)"; fi; \
	  $(call xrun,$(CC) $$CFLAGS $$ARGS -o $@ -S $<,COMPILE -S $$ARGS $<) && { $(call cleanasm,$@); }

$(ASM_PROGRAMS): %: %.s
	@ARGS=$$(grep '^//!' $< | sed 's/.*! *//'); \
	  CFLAGS="`echo "$(CFLAGS)" | sed 's/ *-g */ /'`"; \
	  if test -z "$$ARGS"; then ARGS="$(DEFAULT_ASM_CFLAGS)"; fi; \
	  $(call xrun,$(CC) $$CFLAGS $$ARGS -o $@ $<,ASSEMBLE $@)


clean:
	$(call run,rm -f $(ALLPROGRAMS) *.o *.dSYM *.core,CLEAN)
	$(call run,rm -rf $(DEPSDIR))
	$(call run,for i in $(ASMS); do x=`basename -s .s $$i`; if grep main $$i $$x.c >/dev/null 2>&1; then rm -f $$x; fi; if test -r $$x.c; then rm -f $$i; fi; done)

insert-f%:
	../common/renumber.pl -i f$*
delete-f%:
	../common/renumber.pl -d f$*

.PHONY: all clean insert-f% delete-f%

