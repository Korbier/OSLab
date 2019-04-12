#include "../libs/gdt.h"
#include "../drivers/screen.h"


int  main();

void initGdt();
void initIdt();

void _start(void) {

  cls();

  cursor( 0, 0 );
  style( COLOR_WHITE, COLOR_BLACK );

  print( "MyOS version 0.0.1\n" );
  print( "---------------------------------------------------------\n" );
  print( "Loading : \n" );

  initGdt();
  initIdt();

  main();

}

int main() {

    while(1);

}

void printOK() {
 cursor( 40, cursorY() );
 style( COLOR_LIGHT_GREEN, COLOR_BLACK );
 print("OK\n");
 style( COLOR_WHITE, COLOR_BLACK );
}

void printUnderDev() {
 cursor( 40, cursorY() );
 style( COLOR_LIGHT_CYAN, COLOR_BLACK );
 print("Under development\n");
 style( COLOR_WHITE, COLOR_BLACK );
}

void initGdt() {
  print( " . Global descriptor table (GDT)" );
  init_gdt();
  asm("movw $0x18, %ax \n \
    movw %ax, %ss \n \
    movl $0x20000, %esp \
  ");
  printOK();
}

void initIdt() {
  print( " . Interrupt descriptor table (IDT)" );
  printUnderDev();
}
