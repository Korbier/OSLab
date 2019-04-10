#include "screen.h"

void _start(void) {

  clearscreen();

  setCursor( 0, 0 );
  print( "Loading kernel ...\0", COLOR_WHITE, COLOR_BLACK );
  setCursor( 0, 1 );
  print( "GDT ... loaded.\0", COLOR_WHITE, COLOR_BLACK );
  setCursor( 0, 2 );
  print( "IDT ... loaded.\0", COLOR_WHITE, COLOR_BLACK );

  while(1);

}
