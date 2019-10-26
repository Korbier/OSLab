#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "../drivers/clock.h"
#include "syscall.h"
#include "types.h"

void isr_default_int(void) {
	print("default interrupt\n");
}

void isr_clock_int(void) {
	clockInterrupt();
}

void isr_kbd_int(void) {
	keyboardInterrupt();
}

void do_syscall_int( int sys_num ) {
	syscalls( sys_num );
}