; GDT

setGDT:
  ; calcul de la base de la gdt
  xor eax, eax      ; calcule l'adresse linéaire de GDT
  xor ebx, ebx
  mov ax, ds
  mov ecx, eax
  shl ecx, 4
  mov bx, gdt_start
  add ecx, ebx
  mov dword [gdt_descriptor+2], ecx
  ; Setting gdt
  cli
  lgdt [gdt_descriptor]
  ret


gdt_start:
gdt_null: db 0, 0, 0, 0, 0, 0, 0, 0; null descriptor
gdt_code: db 0xFF, 0xFF, 0x0, 0x0, 0x0, 10011011b, 11011111b, 0x0
gdt_data: db 0xFF, 0xFF, 0x0, 0x0, 0x0, 10010011b, 11011111b, 0x0
gdt_end:
; GDT Descriptor
gdt_descriptor:
  dw gdt_end - gdt_start - 1
  dd gdt_start
  
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
