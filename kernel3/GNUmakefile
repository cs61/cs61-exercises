IMAGE = os01.img
all: $(IMAGE)

# '$(V)' controls whether the lab makefiles print verbose commands (the
# actual shell commands run by Make), as well as the "overview" commands
# (such as '+ cc lib/readline.c').
#
# For overview commands only, run 'make all'.
# For overview and verbose commands, run 'make V=1 all'.
V = 0
ifeq ($(V),1)
compile = $(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(1)
link = $(LD) $(LDFLAGS) $(1)
run = $(1) $(3)
else
compile = @/bin/echo " " $(2) $< && $(CC) $(CPPFLAGS) $(CFLAGS) $(DEPCFLAGS) $(1)
link = @/bin/echo " " $(2) $(patsubst %.full,%,$@) && $(LD) $(LDFLAGS) $(1)
run = @$(if $(2),/bin/echo " " $(2) $(3) &&,) $(1) $(3)
endif

-include build/rules.mk


# Object sets

BOOT_OBJS = $(OBJDIR)/bootstart.o $(OBJDIR)/boot.o

KERNEL_OBJS = $(OBJDIR)/k-exception.o $(OBJDIR)/kernel.o \
	$(OBJDIR)/k-hardware.o $(OBJDIR)/k-loader.o $(OBJDIR)/lib.o
KERNEL_LINKER_FILES = link/kernel.ld link/shared.ld

PROCESS_BINARIES = $(OBJDIR)/p-tom $(OBJDIR)/p-ginny
PROCESS_BINARIES_FULL = $(patsubst %,%.full,$(PROCESS_BINARIES))
PROCESS_LIB_OBJS = $(OBJDIR)/lib.o $(OBJDIR)/process.o
PROCESS_OBJS = $(patsubst %,%.o,$(PROCESS_BINARIES)) $(PROCESS_LIB_OBJS)


# Generic rules for making object files

$(PROCESS_OBJS): $(OBJDIR)/%.o: %.c $(BUILDSTAMPS)
	$(call compile,-O1 -DWEENSYOS_PROCESS -c $< -o $@,COMPILE)

$(OBJDIR)/%.o: %.c $(BUILDSTAMPS)
	$(call compile,-DWEENSYOS_KERNEL -c $< -o $@,COMPILE)

$(OBJDIR)/boot.o: $(OBJDIR)/%.o: boot.c $(BUILDSTAMPS)
	$(call compile,-Os -fomit-frame-pointer -c $< -o $@,COMPILE)

$(OBJDIR)/%.o: %.S $(BUILDSTAMPS)
	$(call compile,-c $< -o $@,ASSEMBLE)


# Specific rules for WeensyOS

$(OBJDIR)/kernel.full: $(KERNEL_OBJS) $(PROCESS_BINARIES) $(KERNEL_LINKER_FILES)
	$(call link,-T $(KERNEL_LINKER_FILES) -nostdlib -o $@ $(KERNEL_OBJS) -b binary $(PROCESS_BINARIES),LINK)

$(PROCESS_BINARIES_FULL): \
$(OBJDIR)/p-%.full: $(OBJDIR)/p-%.o $(PROCESS_LIB_OBJS) \
		link/p-%.ld link/shared.ld
	$(call link,-T link/p-$*.ld link/shared.ld -nostdlib -o $@ $< $(PROCESS_LIB_OBJS),LINK)

$(OBJDIR)/%: $(OBJDIR)/%.full
	$(call run,$(OBJDUMP) -S $< >$@.asm)
	$(call run,$(NM) -n $< >$@.sym)
	$(call run,$(OBJCOPY) -j .text -j .rodata -j .data -j .bss $<,STRIP,$@)

$(OBJDIR)/bootsector: $(BOOT_OBJS) link/boot.ld link/shared.ld
	$(call link,-T link/boot.ld link/shared.ld -nostdlib -o $@.full $(BOOT_OBJS),LINK)
	$(call run,$(OBJDUMP) -S $@.full >$@.asm)
	$(call run,$(NM) -n $@.full >$@.sym)
	$(call run,$(OBJCOPY) -S -O binary -j .text $@.full $@)

$(OBJDIR)/mkbootdisk: build/mkbootdisk.c $(BUILDSTAMPS)
	$(call run,$(HOSTCC) -I. -o $(OBJDIR)/mkbootdisk,HOSTCOMPILE,build/mkbootdisk.c)

os01.img: $(OBJDIR)/mkbootdisk $(OBJDIR)/bootsector $(OBJDIR)/kernel
	$(call run,$(OBJDIR)/mkbootdisk $(OBJDIR)/bootsector $(OBJDIR)/kernel > $@,CREATE $@)


run-%: run-qemu-%
	@:

run-qemu-%: run-$(QEMUDISPLAY)-%
	@:

run-graphic-%: %.img check-qemu
	$(call run,$(QEMU_PRELOAD) $(QEMU) $(QEMUOPT) $(QEMUIMG),QEMU $<)

run-console-%: %.img check-qemu
	$(call run,$(QEMU_PRELOAD) $(QEMU) $(QEMUOPT) -curses $(QEMUIMG),QEMU $<)

run-monitor-%: %.img check-qemu
	$(call run,$(QEMU_PRELOAD) $(QEMU) $(QEMUOPT) -monitor stdio $(QEMUIMG),QEMU $<)

run-gdb-%: run-gdb-$(QEMUDISPLAY)-%
	@:

run-gdb-graphic-%: %.img check-qemu
	$(call run,$(QEMU_PRELOAD) $(QEMU) $(QEMUOPT) -S -gdb tcp::1234 $(QEMUIMG) &,QEMU $<)
	$(call run,gdb -x .gdbinit,GDB)

run-gdb-console-%: %.img check-qemu
	$(call run,$(QEMU_PRELOAD) $(QEMU) $(QEMUOPT) -curses -S -gdb tcp::1234 $(QEMUIMG),QEMU $<)

run: run-qemu-$(basename $(IMAGE))
run-qemu: run-qemu-$(basename $(IMAGE))
run-graphic: run-graphic-$(basename $(IMAGE))
run-console: run-console-$(basename $(IMAGE))
run-monitor: run-monitor-$(basename $(IMAGE))
run-quit: run-quit-$(basename $(IMAGE))
run-gdb: run-gdb-$(basename $(IMAGE))
run-gdb-graphic: run-gdb-graphic-$(basename $(IMAGE))
run-gdb-console: run-gdb-console-$(basename $(IMAGE))
run-graphic-gdb: run-gdb-graphic-$(basename $(IMAGE))
run-console-gdb: run-gdb-console-$(basename $(IMAGE))


# Kill all my qemus
kill:
	-killall -u $$(whoami) $(QEMU)
	@sleep 0.2; if ps -U $$(whoami) | grep $(QEMU) >/dev/null; then killall -9 -u $$(whoami) $(QEMU); fi
