#include "syscall.h"
#include "mem.h"
#include "gdt.h"
#include "../drivers/screen.h"

void syscalls(int sys_num) {
        
        uint16_t ds_select;
        uint32_t ds_base;

        struct gdt_descriptor *ds;
        char *message;

        if (sys_num == 1) {

            print("syscall 1 - Debut\n");

            asm("	mov 44(%%ebp), %%eax	\n \
                mov %%eax, %0		\n \
                mov 24(%%ebp), %%ax	\n \
                mov %%ax, %1" : "=m"(message), "=m"(ds_select) : );

            ds = (struct gdt_descriptor *) (GDTBASE + (ds_select & 0xF8));
            ds_base = ds->base0_15 + (ds->base16_23 << 16) + (ds->base24_31 << 24);

            print((char*) (ds_base + message));
                    
            print("syscall 1 - Fin\n");


        } else {
                print("syscall\n");
        }

        return;
}