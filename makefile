CC=gcc
CC_FLAGS=-m32 -fno-pie -ffreestanding -Wall

LD=ld
LD_FLAGS= -m elf_i386 --oformat binary -Ttext 0x1000

DIR_DIST=dist
DIR_BUILD=build
DIR_LOG=logs
DIR_SRC=src

IMAGE=$(DIR_DIST)/os-image

C_SOURCES = $(wildcard src/kernel/*.c src/libs/*.c src/drivers/*.c)
C_HEADERS = $(wildcard src/kernel/*.h stc/libs/*.h src/drivers/*.h)

OBJ = ${C_SOURCES:.c=.o}

all: $(IMAGE)

run: all
	bochs -q -rc conf/bochs-skip-debug.rc -qf conf/bochsrc.txt 'floppya: 1_44=$(IMAGE), status=inserted'

$(IMAGE): $(DIR_BUILD)/boot.bin $(DIR_BUILD)/kernel.bin
	cat $^ /dev/zero | dd of=$@ bs=512 count=2880 iflag=fullblock

$(DIR_BUILD)/boot.bin: $(DIR_SRC)/boot/boot.asm
	nasm -f bin -o $@ $^

$(DIR_BUILD)/kernel.bin: ${OBJ}
	$(LD) $(LD_FLAGS) $^ -o $@

%.o:%.c
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -rf $(DIR_DIST)/* $(DIR_BUILD)/* $(DIR_LOG)/*
	rm -rf $(DIR_SRC)/kernel/*.o $(DIR_SRC)/libs/*.o $(DIR_SRC)/drivers/*.o
