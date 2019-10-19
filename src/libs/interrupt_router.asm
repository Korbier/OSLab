extern isr_default_int, isr_clock_int, isr_kbd_int
global _asm_default_int, _asm_irq_0, _asm_irq_1

; Encapsulation assembleur de l'appel a la methode C isr_default_int car en C, on ne peut pas appeler iret
_asm_default_int:
	call isr_default_int
	mov al,0x20 ; Ces deux lignes signifient au controlleur
	out 0x20,al ; que l'interruption est traité
	iret

; Encapsulation assembleur de l'appel a la methode C isr_clock_int car en C, on ne peut pas appeler iret
_asm_irq_0:
	call isr_clock_int
	mov al,0x20 ; Ces deux lignes signifient au controlleur
	out 0x20,al ; que l'interruption est traité
	iret

; Encapsulation assembleur de l'appel a la methode C isr_kbd_int car en C, on ne peut pas appeler iret
_asm_irq_1:
	call isr_kbd_int
	mov al,0x20 ; Ces deux lignes signifient au controlleur
	out 0x20,al ; que l'interruption est traité
	iret

