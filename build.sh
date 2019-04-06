#!/bin/bash
echo 'cleaning ...'
rm build/*
rm logs/*
echo 'compiling bootloader ...'
nasm -f bin -o build/boot.bin src/boot.asm
echo 'compiling kernel ...'
nasm -f bin -o build/kernel.bin src/kernel.asm
echo 'creating disk image ...'
cat build/boot.bin build/kernel.bin /dev/zero | dd of=build/boot.img bs=512 count=2880
echo 'launching emulation ...'
bochs -qf conf/bochsrc.txt
