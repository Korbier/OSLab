#include "../libs/gdt.h"
#include "../libs/idt.h"
#include "../libs/pic.h"
#include "../libs/asm.h"
#include "../drivers/screen.h"

int  main();

void initGdt();
void initIdt();
void initPic();

void _start(void) {

  cls();

  position( 0, 0 );
  style( COLOR_WHITE, COLOR_BLACK );

  print( "  MYcOSe version 0.0.1\n" );
  print( "-------------------------------------------------------------------\n" );
  print( "  Loading : \n" );

  initGdt();
  initIdt();
  initPic();

  print( "-------------------------------------------------------------------\n" );
  showCursor();

  //Remise en route des interruptions
  sti;
  
  main();

}

int main() {
  
    while(1);

}

void printOK() {
 position( 50, positionY() );
 style( COLOR_LIGHT_GREEN, COLOR_BLACK );
 print("OK\n");
 style( COLOR_WHITE, COLOR_BLACK );
}

void printUnderDev() {
 position( 50, positionY() );
 style( COLOR_LIGHT_CYAN, COLOR_BLACK );
 print("Under development\n");
 style( COLOR_WHITE, COLOR_BLACK );
}

void initGdt() {
  print( "  . Global descriptor table (GDT)" );
  init_gdt();
  asm("movw $0x18, %ax \n \
    movw %ax, %ss \n \
    movl $0x20000, %esp \
  ");
  printOK();
}

void initIdt() {
  print( "  . Interrupt descriptor table (IDT)" );
  init_idt();
  printOK();
}

void initPic() {
  print( "  . Programmable Interrupt Controller (PIC)" );
  init_pic();
  printOK();
}