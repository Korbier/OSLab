#ifndef _MYOS_GDT_
#define _MYOS_GDT_

#include "types.h"

#define GDTBASE    0x0		/* addr. physique ou doit resider la gdt */
#define GDTSIZE    0xFF		/* nombre max. de descripteurs dans la table */

extern void init_gdt();

struct gdt_descriptor {
  uint16_t lim0_15;
  uint16_t base0_15;
  uint8_t  base16_23;
  uint8_t  acces;
  uint8_t  lim16_19 : 4;
  uint8_t  other : 4;
  uint8_t  base24_31;
} __attribute__ ((packed));

struct gdt_register {
    uint16_t limite ;
    uint32_t base ;
} __attribute__ ((packed));


#endif
