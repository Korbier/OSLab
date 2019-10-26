#include "types.h"
#include "mem.h"
#include "gdt.h"

static struct gdt_descriptor kgdt[GDTSIZE];	/* GDT */
static struct gdt_register   kgdtr;	      	/* GDTR */

/*
 * 'init_desc' initialise un descripteur de segment situe en gdt ou en ldt.
 * 'descriptor' est l'adresse lineaire du descripteur a initialiser.
 */
void init_gdt_descriptor(uint32_t base, uint32_t limite, uint8_t acces, uint8_t other, struct gdt_descriptor * descriptor) {
	descriptor->lim0_15   = (limite & 0xffff);
	descriptor->base0_15  = (base & 0xffff);
	descriptor->base16_23 = (base & 0xff0000) >> 16;
	descriptor->acces     = acces;
	descriptor->lim16_19  = (limite & 0xf0000) >> 16;
	descriptor->other     = (other & 0xf);
	descriptor->base24_31 = (base & 0xff000000) >> 24;
}

/*
 * Cette fonction initialise la GDT apres que le kernel soit charge
 * en memoire. Une GDT est deja operationnelle, mais c'est celle qui
 * a ete initialisee par le secteur de boot et qui ne correspond
 * pas forcement a celle que l'on souhaite.
 */
void init_gdt() {

	/* Premier descripteur null */
	init_gdt_descriptor(0x0, 0x0,     0x0,  0x0,  &kgdt[0]);

	/* Descripteurs de segments pour le noyau */
	init_gdt_descriptor(0x0, 0xFFFFF, 0x9B, 0x0D, &kgdt[1]);
	init_gdt_descriptor(0x0, 0xFFFFF, 0x93, 0x0D, &kgdt[2]);
	init_gdt_descriptor(0x0, 0x0,     0x97, 0x0D, &kgdt[3]);

	/* descripteur de segments en mode utilisateur */
	init_gdt_descriptor(0x30000, 0x1, 0xFF, 0x0D, &kgdt[4]); /* ucode */
	init_gdt_descriptor(0x30000, 0x1, 0xF3, 0x0D, &kgdt[5]); /* udata */
	init_gdt_descriptor(0x0,     0x0, 0xF7, 0x0D, &kgdt[6]); /* ustack */

	/* tss */
	default_tss.debug_flag = 0x00;
	default_tss.io_map     = 0x00;
	default_tss.esp0       = 0x20000;
	default_tss.ss0        = 0x18;
	init_gdt_descriptor((uint32_t) & default_tss, 0x67, 0xE9, 0x00, &kgdt[7]);

	kgdtr.limite = GDTSIZE * 8;
	kgdtr.base   = GDTBASE;

	memcpy((int8_t *) kgdtr.base, (int8_t *) kgdt, kgdtr.limite);

	asm("lgdtl (kgdtr)");

	asm(
    "movw $0x10, %ax\n \
     movw %ax,   %ds\n \
     movw %ax,   %es\n \
     movw %ax,   %fs\n \
     movw %ax,   %gs\n \
     ljmp $0x08, $next\n \
     next:\n"
  );

}
