#ifndef _MYOS_SCREEN_
#define _MYOS_SCREEN_

#include "../libs/types.h"

#define COLOR_BLACK         0x0
#define COLOR_BLUE          0x1
#define COLOR_GREEN         0x2
#define COLOR_CYAN          0x3
#define COLOR_RED           0x4
#define COLOR_MAGENTA       0x5
#define COLOR_BROWN         0x6
#define COLOR_LIGHT_GREY    0x7
#define COLOR_DARK_GREY     0x8
#define COLOR_LIGHT_BLUE    0x9
#define COLOR_LIGHT_GREEN   0xA
#define COLOR_LIGHT_CYAN    0xB
#define COLOR_LIGHT_RED     0xC
#define COLOR_LIGHT_MAGENTA 0xD
#define COLOR_YELLOW        0xE
#define COLOR_WHITE         0xF

extern void position( int8_t x, int8_t y );
extern int8_t positionX();
extern int8_t positionY();
extern void style( int8_t foreground, int8_t background );
extern void print( char * string );
extern void printc( char character );
extern void cls();
extern void scroll();

extern void moveCursor( uint8_t x, uint8_t y );
extern void showCursor();

#endif
