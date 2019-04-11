#include "screen.h"

#define VIDEO_MEMORY_ADDR 0xB8000
#define SCREEN_WITH       80
#define SCREEN_HEIGHT     25

int8_t cAttr = 0x0F;
int8_t cX    = 0;
int8_t cY    = 0;

void printc( int8_t character );

void cursor( int8_t x, int8_t y ) {
  cX = x;
  cY = y;
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
      cursor(x, y);
      printc( 0x0 );
    }
  }
}

void scroll() {

}

extern void printc( int8_t character ) {

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


/*
void setAttributes( int8_t forecolor, int8_t backcolor ) {
  cAttr = (backcolor << 4) | (forecolor & 0x0F);
}

void printc( int8_t character ) {

  //Selection de l'emplacement memoire ou ecrire
  int8_t * vram = ( int8_t * ) VIDEO_MEMORY_ADDR + ( cY * ( SCREEN_WITH * 2 ) + ( cX * 2 ) );

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

void setCursor( int8_t x, int8_t y ) {
  cX = x;
  cY = y;
}

void clearscreen() {
  for ( int8_t x=0; x<SCREEN_WITH; x++ ) {
    for ( int8_t y=0; y<SCREEN_HEIGHT; y++ ) {
      setCursor(x, y);
      printc( ' ' );
    }
  }
}

void print( int8_t * string, int8_t forecolor, int8_t backcolor ) {
  setAttributes(forecolor, backcolor);
  while ( *string != 0 ) {
    printc( (int8_t) *string );
    string++;
  }
}
*/
