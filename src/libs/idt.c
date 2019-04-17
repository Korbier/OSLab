#include "types.h"
#include "mem.h"
#include "idt.h"

void _asm_default_int(void);
void _asm_irq_0(void);
void _asm_irq_1(void);

static struct idt_descriptor kidt[IDTSIZE]; /* Table de IDT */
static struct idt_register   kidtr;         /* Registre IDTR */

/*
 * 'init_idt_descriptor' initialise un descripteur de segment situe en idt.
 * 'desc' est l'adresse lineaire du descripteur a initialiser.
 * L'argument 'type' doit avoir pour valeur INTGATE, TRAPGATE
 * ou TASKGATE.
 */
void init_idt_descriptor(uint16_t select, uint32_t offset, uint16_t type, struct idt_descriptor *desc) {
	desc->offset0_15 = (offset & 0xffff);
	desc->select = select;
	desc->type = type;
	desc->offset16_31 = (offset & 0xffff0000) >> 16;
	return;
}

/*
 * Cette fonction initialise la IDT apres que le kernel soit charge 
 * en memoire. 
 */
void init_idt() {

	/* Initialisation des descripteurs systeme par defaut */
	for (int i = 0; i < IDTSIZE; i++)  {
		init_idt_descriptor(0x08, (uint32_t) _asm_default_int, INTGATE, &kidt[i]);
	}

	init_idt_descriptor(0x08, (uint32_t) _asm_irq_0, INTGATE, &kidt[32]);	/* horloge */
	init_idt_descriptor(0x08, (uint32_t) _asm_irq_1, INTGATE, &kidt[33]);	/* clavier */

	/* Initialisation de la structure pour IDTR */
	kidtr.limite = IDTSIZE * 8;
	kidtr.base = IDTBASE;

	/* Recopie de la IDT a son adresse */
	memcpy((char *) kidtr.base, (char *) kidt, kidtr.limite);

	/* Chargement du registre IDTR */
	asm("lidtl (kidtr)");

}
