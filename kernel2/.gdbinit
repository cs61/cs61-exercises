init-if-undefined $target_set = 0
if $target_set == 0
    set arch i386:x86-64
    target remote localhost:1234
    file obj/kernel.full
    add-symbol-file obj/bootsector.full 0x7c00
    add-symbol-file obj/p-hello.full 0x100000
    add-symbol-file obj/p-welcome.full 0x140000
    source build/functions.gdb
    display/5i $pc
    set $target_set = 1
end
