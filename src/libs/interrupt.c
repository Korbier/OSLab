#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "../drivers/clock.h"
#include "types.h"

void isr_default_int(void) {
	print("default interrupt\n");
}

void isr_GP_exc(void) {
	print("GP fault\n");
	while (1);
}

void isr_clock_int(void) {
	clockInterrupt();
}

void isr_kbd_int(void) {
	keyboardInterrupt();
}