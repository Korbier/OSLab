#ifndef _MYOS_SCEEN_
#define _MYOS_SCEEN_

#include "../kernel/types.h"

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

extern void cursor( int8_t x, int8_t y );
extern void style( int8_t foreground, int8_t background );
extern void print( int8_t * string );
extern void cls();
extern void scroll();

/*
extern void setCursor( int8_t x, int8_t y );
extern void clearscreen();
extern void print( int8_t * string, int8_t forecolor, int8_t backcolor );
*/

#endif
