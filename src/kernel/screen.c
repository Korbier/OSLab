#include "screen.h"

#define VIDEO_MEMORY_ADDR 0xB8000
#define SCREEN_WITH       80
#define SCREEN_HEIGHT     25

u8 cAttr = 0x0F;
u8 cX    = 0;
u8 cY    = 0;

void setAttributes( u8 forecolor, u8 backcolor ) {
  cAttr = (backcolor << 4) | (forecolor & 0x0F);
}

void printc( u8 character ) {

  //Selection de l'emplacement memoire ou ecrire
  u8 * vram = ( u8 * ) VIDEO_MEMORY_ADDR + ( cY * ( SCREEN_WITH * 2 ) + ( cX * 2 ) );

  //Ecriture
  *vram     = character;
  *(vram+1) = cAttr;

  //Increment de cX, cY
  cX++;
  if ( cX >= SCREEN_WITH ) {
    cY++;
    cX = 0;
  }

}

void setCursor( u8 x, u8 y ) {
  cX = x;
  cY = y;
}

void clearscreen() {
  for ( u8 x=0; x<SCREEN_WITH; x++ ) {
    for ( u8 y=0; y<SCREEN_HEIGHT; y++ ) {
      setCursor(x, y);
      printc( ' ' );
    }
  }
}

void print( u8 * string, u8 forecolor, u8 backcolor ) {
  setAttributes(forecolor, backcolor);
  while ( *string != 0 ) {
    printc( (u8) *string );
    string++;
  }
}
