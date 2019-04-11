#include "../drivers/screen.h"

void _start(void) {

  cls();

  cursor( 0, 0 );
  print( "Loading kernel ...\n" );
  print( "GDT ... loaded.\n" );
  print( "IDT ... loaded.\n" );

  main();
  
}

int main() {

    while(1);

}
