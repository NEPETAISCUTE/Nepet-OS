add-symbol-file kernel.elf
set disassembly-flavor intel
target remote | qemu-system-x86_64 -S -gdb stdio -m 16 -boot c -hda ../barebones.iso
