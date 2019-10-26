#include "clock.h"
#include "screen.h"

void clockInterrupt() {
    static int tic = 0;
	static int sec = 0;
	tic++;
	if (tic % 100 == 0) {
		sec++;
		tic = 0;
		print(".");
	}
}