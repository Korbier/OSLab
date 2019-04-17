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

#endif