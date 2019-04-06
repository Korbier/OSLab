[BITS 16]  ; indique a Nasm que l'on travaille en 16 bits
[ORG 0x0]

%define BASE  0x100  ; 0x0100:0x0 = 0x1000
%define KSIZE 1  ; nombre de secteurs de 512 octets à charger

jmp start
%include "src/display.inc"
start:

; initialisation des segments en 0x07C00
mov ax, 0x07C0
mov ds, ax
mov es, ax
mov ax, 0x8000
mov ss, ax
mov sp, 0xf000    ; pile de 0x8F000 -> 0x80000

; affiche un msg
mov si, welcomeMessage
call display

; charger le noyau
xor ax, ax        ; reset floppy disk function
mov dl, [bootdrv] ; drive 0 is floppy drive
int 0x13          ; call BIOS interrupt

push es           ; Sauvegarde du registre es

mov ax, BASE      ; we are going to read sector to into address 0x1000:0
mov es, ax
xor bx, bx

mov ah, 0x02      ; read floppy sector function
mov al, KSIZE     ; read 1 sector
mov ch, 0         ; we are reading the second sector past us, so its still on track 1
mov cl, 2         ; sector to read (The second sector)
mov dh, 0         ; head number
mov dl, [bootdrv] ; drive number. Remember Drive 0 is floppy drive.
int 0x13          ; call BIOS - Read the sector

pop es ; restore es

jmp dword BASE:0; saut vers le kernel

;--- Variables ---
welcomeMessage db "Loading kernel ...", 13, 10, 0
bootdrv: db 0
;-----------------

;--- NOP jusqu'à 510 ---
times 510-($-$$) db 144
dw 0xAA55
