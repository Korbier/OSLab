[BITS 32]
[ORG 0x1000]

; Affichage d'un message par écriture dans la RAM vidéo
    mov byte [0xB8000], 'H'
    mov byte [0xB8001], 0x57
    mov byte [0xB8002], 'E'
    mov byte [0xB8003], 0x0A
    mov byte [0xB8004], 'L'
    mov byte [0xB8005], 0x4E
    mov byte [0xB8006], 'L'
    mov byte [0xB8007], 0x62
    mov byte [0xB8008], 'O'
    mov byte [0xB8009], 0x0E

end:
    jmp end
