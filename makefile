all: dist/floppy.img

run: all
	bochs -qf conf/bochsrc.txt

dist/floppy.img: build/boot.bin build/kernel.bin
	cat build/boot.bin build/kernel.bin /dev/zero | dd of=dist/floppy.img bs=512 count=2880 iflag=fullblock

build/boot.bin: src/boot/boot.asm
	nasm -f bin -o build/boot.bin src/boot/boot.asm

build/kernel.bin:  src/kernel/kernel.c
	gcc -c src/kernel/kernel.c -o build/kernel.o
	ld --oformat binary -Ttext 1000 build/kernel.o -o build/kernel.bin

#build/kernel.bin: src/kernel/kernel.asm
#	nasm -f bin -o build/kernel.bin src/kernel/kernel.asm

clean:
	rm -rf build/*
	rm -rf logs/*
