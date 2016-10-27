init-if-undefined $loaded = 0
if $loaded == 0
    set $loaded = 1
    set arch i386:x86-64
    file obj/kernel.full
    add-symbol-file obj/bootsector.full 0x7c00
    add-symbol-file obj/p-tom.full 0x100000
    add-symbol-file obj/p-ginny.full 0x140000
    target remote localhost:1234
    source build/functions.gdb
    display/5i $pc

    # Your initialization commands here (if you want)
end
