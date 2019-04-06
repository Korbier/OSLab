all: clean dist/floppy.img

run: all
	bochs -qf conf/bochsrc.txt

dist/floppy.img: build/boot.bin build/kernel.bin
	cat build/boot.bin build/kernel.bin /dev/zero | dd of=dist/floppy.img bs=512 count=2880

build/boot.bin: src/boot.asm
	nasm -f bin -o build/boot.bin src/boot.asm

build/kernel.bin: src/kernel.asm
	nasm -f bin -o build/kernel.bin src/kernel.asm

clean:
	rm -rf build/*
	rm -rf logs/*
