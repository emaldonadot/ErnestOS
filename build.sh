clear
nasm -f elf32 kernel.asm -o kasm.o
gcc -m32 -c kernel.c -o kc.o
ld -m elf_i386 -T link.ld -o ErnestOS/boot/kernel.bin kasm.o kc.o
rm kasm.o
rm kc.o
ls -ltr

grub-mkrescue -o ErnestOS.iso ErnestOS/

qemu-system-i386  -curses -kernel ErnestOS/boot/kernel.bin


