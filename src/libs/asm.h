#ifndef _MYOS_ASM_
#define _MYOS_ASM_

/* Desactivation des interruptions */
#define cli asm("cli"::)

/* Reactivation des interruptions */
#define sti asm("sti"::)

/* Ecriture d'un octet sur un port */
#define outb(port, value) \
	asm volatile ("outb %%al, %%dx" :: "d" (port), "a" (value));

/* écrit un octet sur un port et marque une temporisation */
#define outbp(port,value) \
	asm volatile ("outb %%al, %%dx; jmp 1f; 1:" :: "d" (port), "a" (value));

/* lit un octet sur un port */
#define inb(port) ({ \
	unsigned char _v; \
	asm volatile ("inb %%dx, %%al" : "=a" (_v) : "d" (port)); \
	_v; \
})

#define switchToUserTask(esp0) ({ \
	asm("cli \n \
		push $0x33 \n \
		push $0x30000 \n \
		pushfl \n \
		popl %%eax \n \
		orl $0x200, %%eax \n \
		and $0xFFFFBFFF, %%eax \n \
		push %%eax \n \
		push $0x23 \n \
		push $0x0 \n \
		movl $0x20000, %0 \n \
		movw $0x2B, %%ax \n \
		movw %%ax, %%ds \n \
		iret":"=m"(esp0):); \
})

#endif