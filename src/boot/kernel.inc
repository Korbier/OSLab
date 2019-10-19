loadKernel:
  
  ; récupération de l'unité de boot
  mov [bootdrv], dl

  ; chargement du moyau
  reset:
    xor ax, ax        ; reset floppy disk function
    int 0x13          ; call BIOS interrupt
    jc reset

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
  jc reset
  
  pop es ; restore es
  ret

bootdrv: db 0
