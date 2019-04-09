%define BASE  0x100  ; 0x0100:0x0 = 0x1000
%define KSIZE 50     ; nombre de secteurs de 512 octets à charger

[BITS 16]  ; indique a Nasm que l'on travaille en 16 bits
[ORG 0x0]

jmp start
%include "src/boot/display.inc"
%include "src/boot/kernel.inc"
%include "src/boot/gdt.inc"
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

  call loadKernel
  call setGDT

  ; affiche un msg
  mov si, switchToPModeMessage
  call display

  ; Switch to protected mode
  mov eax, cr0
  or  eax, 1
  mov cr0, eax
  jmp pmode

pmode:
  mov ax, DATA_SEG ; Now in PM , our old segments are meaningless ,
  mov ds, ax ; so we point our segment registers to the
  mov ss, ax ; data selector we defined in our GDT
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov esp, 0x9F000 ; Update our stack position so it
  jmp dword CODE_SEG:0x1000

; Variables
welcomeMessage:       db 'Loading kernel ...', 13, 10, 0
switchToPModeMessage: db 'Switching to 32-bit protected mode', 13, 10, 0

;--- NOP jusqu'à 510 ---
times 510-($-$$) db 144
dw 0xAA55
