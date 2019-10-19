#include "screen.h"
#include "../libs/asm.h"

#define VIDEO_MEMORY_ADDR 0xB8000
#define SCREEN_WITH       80
#define SCREEN_HEIGHT     25

int8_t cAttr = 0x0F;
int8_t cX    = 0;
int8_t cY    = 0;

void printc( int8_t character );

void position( int8_t x, int8_t y ) {
  cX = x;
  cY = y;
}

int8_t positionX() {
  return cX;
}

int8_t positionY() {
  return cY;
}

void style( int8_t foreground, int8_t background ) {
  cAttr = (background << 4) | (foreground & 0x0F);
}

void print( int8_t * string ) {
  while ( *string != 0 ) {
    printc( (int8_t) *string );
    string++;
  }
}

void cls() {
  for ( int8_t x=0; x<SCREEN_WITH; x++ ) {
    for ( int8_t y=0; y<SCREEN_HEIGHT; y++ ) {
      position(x, y);
      printc( 0x0 );
    }
  }
}

void scroll() {

}

void printc( int8_t character ) {

    //Selection de l'emplacement memoire ou ecrire
    int8_t * vram = ( int8_t * ) VIDEO_MEMORY_ADDR + ( cY * ( SCREEN_WITH * 2 ) + ( cX * 2 ) );

    if ( character == '\n' ) {
      cX = 0;
      cY++;
    } else {

      *vram     = character;
      *(vram+1) = cAttr;

      //Increment de cX, cY
      cX++;
      if ( cX >= SCREEN_WITH ) {
        cY++;
        cX = 0;
      }

    }

    if ( cY >= SCREEN_HEIGHT ) {
      scroll();
    }

}

void moveCursor( uint8_t x, uint8_t y ) {
  uint16_t c_pos;
  c_pos = y * 80 + x;
  outb(0x3d4, 0x0f);
  outb(0x3d5, (uint8_t) c_pos);
  outb(0x3d4, 0x0e);
  outb(0x3d5, (uint8_t) (c_pos >> 8));
}

void showCursor() {
  moveCursor(cX, cY);
}
