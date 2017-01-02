COMPILER = gcc
LINKER = ld
ASSEMBLER = nasm

CFLAGS = -m32 -c -ffreestanding
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T src/link.ld
EMULATOR = qemu-system-i386
EMULATOR_FLAGS = -curses -kernel 

SRCS = src/kernel.asm src/kernel.c src/string.c src/system.c src/screen.c
OBJS = obj/kasm.o obj/kc.o obj/string.o obj/system.o obj/screen.o
OUTPUT = ErnestOS/boot/kernel.bin

run:link
	$(EMULATOR) $(EMULATOR_FLAGS) $(OUTPUT)

link:compile $(OBJS)
	rm -r -f ErnestOS/
	mkdir ErnestOS/
	mkdir ErnestOS/boot
	$(LINKER) $(LDFLAGS) -o $(OUTPUT) $(OBJS)

compile:$(SRCS)
	rm obj/ -r -f
	mkdir obj/

obj/kasm.o:src/kernel.asm
	$(ASSEMBLER) $(ASFLAGS) -o obj/kasm.o src/kernel.asm


obj/kc.o:src/kernel.c
	$(COMPILER) $(CFLAGS) -o obj/kc.o src/kernel.c

obj/string.o:src/string.c
	$(COMPILER) $(CFLAGS) -o obj/string.o src/string.c

obj/system.o:src/system.c
	$(COMPILER) $(CFLAGS) -o obj/system.o src/system.c

obj/screen.o:src/screen.c
	$(COMPILER) $(CFLAGS) -o obj/screen.o src/screen.c



build:all
	rm ErnestOS/boot/grub/ -r -f
	mkdir ErnestOS/boot/grub/
	echo set default = 0 >> ErnestOS/boot/grub/grub.cfg
	echo set timeout = 0 >> ErnestOS/boot/grub/grub.cfg
	echo menuentry = "ErnestOS" { >> ErnestOS/boot/grub/grub.cfg
	echo 	set root='(hd96)' >> ErnestOS/boot/grub/grub.cfg
	echo 	multiboot /boot/kernel.bin >> ErnestOS/boot/grub/grub.cfg
	echo } >> ErnestOS/boot/grub/grub.cfg

	grub-mkrescue -o ErnestOS.iso ErnestOS/

clear:
	rm -r -f obj
	rm -f obj/*
	rm -r -f ErnestOS/
