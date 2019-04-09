#include "types.h"

#define VIDEO_MEMORY_ADDR 0xB8000
#define SCREEN_WITH       80
#define SCREEN_HEIGHT     25

// note this example will always write to the top line of the screen
void print( int colour, const char *string ) {

    unsigned char * vram = ( unsigned char * ) VIDEO_MEMORY_ADDR;// + ( y * 80 + x );
    *vram = 'Z';
    *(vram + 1) = 0x41;
/*
    volatile uint16_t * vram = ( volatile uint16_t * ) VIDEO_MEMORY_ADDR;

    while( *string != 0 ) {
        *vram++ = *string++;
        *vram++ = colour;
    }
*/
}
