%define BASE  0x100  ; 0x0100:0x0 = 0x1000
%define KSIZE 50     ; nombre de secteurs de 512 octets à charger

[BITS 16]  ; indique a Nasm que l'on travaille en 16 bits
[ORG 0x0]

jmp start
%include "src/boot/display.inc"
start:

  ; initialisation des segments en 0x07C00
  mov ax, 0x07C0
  mov ds, ax
  mov es, ax
  mov ax, 0x8000
  mov ss, ax
  mov sp, 0xf000    ; pile de 0x8F000 -> 0x80000

  ; récupération de l'unité de boot
  mov [bootdrv], dl

  ; affiche un msg
  mov si, welcomeMessage
  call display

  ; chargement du moyau
  xor ax, ax        ; reset floppy disk function
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

  ; initialisation du pointeur sur la GDT
  mov ax, gdt_end    ; calcule la limite de GDT
  mov bx, gdt_start
  sub ax, bx
  mov word [gdt_descriptor], ax

  xor eax, eax      ; calcule l'adresse linéaire de GDT
  xor ebx, ebx
  mov ax, ds
  mov ecx, eax
  shl ecx, 4
  mov bx, gdt_start
  add ecx, ebx
  mov dword [gdt_descriptor+2], ecx

;  mov si, welcomePModeMessage
;  call display

  ; Switch to protected mode
  cli
  lgdt [gdt_descriptor]
  mov eax, cr0
  or  ax, 1
  mov cr0, eax

  jmp init_pmode

init_pmode:
  mov ax, 0x10; DATA_SEG ; Now in PM , our old segments are meaningless ,
  mov ds, ax ; so we point our segment registers to the
  mov ss, ax ; data selector we defined in our GDT
  mov es, ax
  mov fs, ax
  mov gs, ax

  mov esp, 0x90000 ; Update our stack position so it

  jmp dword 0x8:0x1000

; Variables
welcomeMessage:      db 'Loading kernel ...', 13, 10, 0
bootdrv:             db 0

; GDT
gdt_start:
gdt_null:
  db 0, 0, 0, 0, 0, 0, 0, 0; null descriptor
gdt_code:
  db 0xFF, 0xFF, 0x0, 0x0, 0x0, 10011011b, 11011111b, 0x0
gdt_data:
  db 0xFF, 0xFF, 0x0, 0x0, 0x0, 10010011b, 11011111b, 0x0
gdt_end:
; GDT Descriptor
gdt_descriptor:
  dw 0
  dd 0
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
;--- NOP jusqu'à 510 ---
times 510-($-$$) db 144
dw 0xAA55
