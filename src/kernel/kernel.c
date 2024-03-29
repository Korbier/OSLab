#include "../libs/gdt.h"
#include "../libs/idt.h"
#include "../libs/pic.h"
#include "../libs/asm.h"
#include "../libs/mem.h"
#include "../drivers/screen.h"

int  main();

void initGdt();
void initIdt();
void initPic();
void initTss();

void _start(void) {

  cls();

  position( 0, 0 );
  style( COLOR_WHITE, COLOR_BLACK );

  print( "  MYcOSe version 0.0.1\n" );
  print( "-------------------------------------------------------------------\n" );
  print( "  Loading : \n" );

  initIdt();
  initPic();
  initGdt();
  initTss();

	/* Initialisation du pointeur de pile %esp */
  asm("   movw $0x18, %ax \n \
          movw %ax, %ss \n \
          movl $0x20000, %esp");

  print( "-------------------------------------------------------------------\n" );
  showCursor();

  //Remise en route des interruptions
//  sti;
  
  main();

}

void task1() {

	char *msg = (char *) 0x100;	/* le message sera en 0x30100 */
	msg[0] = 't';
	msg[1] = 'a';
	msg[2] = 's';
	msg[3] = 'k';
	msg[4] = '1';
	msg[5] = 0;

	asm("mov %0, %%ebx; mov $0x01, %%eax; int $0x30"::"m"(msg));
  //asm("mov 0x100, %%ebx; mov $0x01, %%eax; int $0x30"::);
  
	while (1);
	return;			/* never go there */
}

int main() {
  
    //while(1);

  //Copie en memoire de la tache utilisateur
	memcpy((char*) 0x30000, &task1, 100);	

  style( COLOR_RED, COLOR_BLACK );	
  print("Switching to user task (ring3 mode)\n");
  style( COLOR_WHITE, COLOR_BLACK );	

	asm("   cli \n \
		push $0x33 \n \
		push $0x30000 \n \
		pushfl \n \
		popl %%eax \n \
		orl $0x200, %%eax \n \
		and $0xFFFFBFFF, %%eax \n \
		push %%eax \n \
		push $0x23 \n \
		push $0x0 \n \
		movl $0x20000, %0 \n \
		movw $0x2B, %%ax \n \
		movw %%ax, %%ds \n \
		iret": "=m"(default_tss.esp0):);

	print("Critical error, halting system\n");
	asm("hlt");

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

void initTss() {
  print( "  . Task State Segment (TSS)" );
  	/* Initialisation du TSS */
	asm("	movw $0x38, %ax \n \
		ltr %ax");	
  printOK();
}