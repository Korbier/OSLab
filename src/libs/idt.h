#ifndef _MYOS_IDT_
#define _MYOS_IDT_

#define IDTBASE  0x800		/* addr. physique ou doit resider la IDT */
#define IDTSIZE  0xFF		/* nombre max. de descripteurs dans la table */

#define INTGATE  0x8E00		/* utilise pour gerer les interruptions */
#define TRAPGATE 0xEF00		/* utilise pour faire des appels systemes */

extern void init_idt();

/* Descripteur de segment */
struct idt_descriptor {
	uint16_t offset0_15;
	uint16_t select;
	uint16_t type;
	uint16_t offset16_31;
} __attribute__ ((packed));

/* Registre IDTR */
struct idt_register {
	uint16_t limite;
	uint32_t base;
} __attribute__ ((packed));

#endif