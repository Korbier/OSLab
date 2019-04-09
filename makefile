all: dist/floppy.img

run: all
	bochs -q -rc conf/bochs-skip-debug.rc -qf conf/bochsrc.txt

dist/floppy.img: build/boot.bin build/kernel.bin
	cat build/boot.bin build/kernel.bin /dev/zero | dd of=dist/floppy.img bs=512 count=2880 iflag=fullblock

build/boot.bin: src/boot/boot.asm
	nasm -f bin -o build/boot.bin src/boot/boot.asm

build/kernel.bin:  src/kernel/kernel.c
	gcc -m32 -fno-pie -c src/kernel/kernel.c -o build/kernel.o
	ld -m elf_i386 --oformat binary -Ttext 0x1000 build/kernel.o -o build/kernel.bin

clean:
	rm -rf build/*
	rm -rf logs/*
