# are we using clang?
ISCLANG := $(shell if $(CC) --version | grep LLVM >/dev/null; then echo 1; else echo 0; fi)

CC += -std=gnu11 -W -Wall -Wshadow
CFLAGS ?= -g $(DEFS)
O ?= -O3

# these rules ensure dependencies are created
DEPCFLAGS = -MD -MF $(DEPSDIR)/$*.d -MP
DEPSDIR := .deps
BUILDSTAMP := $(DEPSDIR)/rebuildstamp
DEPFILES := $(wildcard $(DEPSDIR)/*.d)
ifneq ($(DEPFILES),)
include $(DEPFILES)
endif

# when the C compiler or optimization flags change, rebuild all objects
ifneq ($(strip $(DEP_CC)),$(strip $(CC) $(CPPFLAGS) $(CFLAGS) $(O)))
DEP_CC := $(shell mkdir -p $(DEPSDIR); echo >$(BUILDSTAMP); echo "DEP_CC:=$(CC) $(CFLAGS) $(O)" >$(DEPSDIR)/_cc.d)
endif

V = 0
ifeq ($(V),1)
run = $(1) $(3)
xrun = /bin/echo "$(1) $(3)" && $(1) $(3)
else
run = @$(if $(2),/bin/echo "  $(2) $(3)" &&,) $(1) $(3)
xrun = $(if $(2),/bin/echo "  $(2) $(3)" &&,) $(1) $(3)
endif

CLEANASM = 1
ifeq ($(CLEANASM),1)
cleanasm = perl -ni -e 'print if !/^(?:\# BB|\s+\.cfi|\s+\.p2align|\s+\# =>This)/' $(1)
else
cleanasm = :
endif

# cancel implicit rules we don't want
%: %.c
%.o: %.c

$(BUILDSTAMP):
	@mkdir -p $(@D)
	@echo >$@

always:
	@:

clean-hook:
	@:

.PHONY: always clean-hook
.PRECIOUS: %.o
