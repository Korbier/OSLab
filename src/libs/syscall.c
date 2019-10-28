#include "syscall.h"
#include "mem.h"
#include "gdt.h"
#include "../drivers/screen.h"

void syscalls(int sys_num) {
        
        uint16_t ds_select;
        uint32_t ds_base;

        struct gdt_descriptor *ds;
        unsigned char *message;

        if (sys_num == 1) {

            print("syscall 1 - start\n");

            asm("	mov 44(%%ebp), %%eax	\n \
                mov %%eax, %0		\n \
                mov 24(%%ebp), %%ax	\n \
                mov %%ax, %1" : "=m"(message), "=m"(ds_select) : );

            ds = (struct gdt_descriptor *) (GDTBASE + (ds_select & 0xF8));
            ds_base = ds->base0_15 + (ds->base16_23 << 16) + (ds->base24_31 << 24);

            print("[");
            print( (char *) 0x30100 );
            print("]\n");
            print("[");
            print( (char *) (ds_base + message));
            print("]\n");
                    
            print("syscall 1 - end\n");


        } else {
            print("syscall\n");
        }

        return;
}