;---------------------------------------------------------
; Synopsis: Affiche une chaîne de caractères se terminant par 0x0
; Entrée:   DS:SI -> pointe sur la chaîne à afficher
;---------------------------------------------------------
display:
  push ax
  push bx
.display_start:
  lodsb         ; ds:si -> al
  or al, al     ; fin chaîne ?
  jz .display_end
  mov ah, 0x0E  ; appel au service 0x0e, int 0x10 du bios
  mov bx, 0x07  ; bx -> attribut, al -> caractère ASCII
  int 0x10
  jmp .display_start
.display_end:
  pop bx
  pop ax
  ret
