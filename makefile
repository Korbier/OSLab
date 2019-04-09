CC=gcc
CC_FLAGS=-m32 -fno-pie -ffreestanding

DIR_DIST=dist
DIR_BUILD=build
DIR_LOG=logs

IMAGE=$(DIR_DIST)/os-image

all: $(IMAGE)

run: all
	bochs -q -rc conf/bochs-skip-debug.rc -qf conf/bochsrc.txt 'floppya: 1_44=$(IMAGE), status=inserted'

$(IMAGE): $(DIR_BUILD)/boot.bin $(DIR_BUILD)/kernel.bin
	cat $(DIR_BUILD)/boot.bin $(DIR_BUILD)/kernel.bin /dev/zero | dd of=$(IMAGE) bs=512 count=2880 iflag=fullblock

$(DIR_BUILD)/boot.bin: src/boot/boot.asm
	nasm -f bin -o $(DIR_BUILD)/boot.bin src/boot/boot.asm

build/kernel.bin: screen.o kernel.o
	ld -m elf_i386 --oformat binary -Ttext 0x1000 $(DIR_BUILD)/*.o -o $(DIR_BUILD)/kernel.bin

%.o: src/kernel/%.c
	$(CC) $(CC_FLAGS) -c $< -o build/$@

clean:
	rm -rf $(DIR_DIST)/* $(DIR_BUILD)/* $(DIR_LOG)/*
