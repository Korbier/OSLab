[BITS 16]
[ORG 0x0]

jmp start

%include "src/display.inc"

start:
; initialisation des segments en 0x100
    mov ax, 0x100
    mov ds, ax
    mov es, ax

; initialisation du segment de pile
    mov ax, 0x8000
    mov ss, ax
    mov sp, 0xf000

; affiche un msg
    mov si, msg00
    call display

end:
    jmp end


msg00: db 'Kernel loaded', 10, 0