#include <math.h>
#include "asuro.h"
#include "print_tsv.h"

#define THRESHOLD 200

enum {
	WHITE,
	BLACK,
};

// brightness: 0..1023
static int next_brightness(int brightness) {
	static int white = -5, state = WHITE;

	if (white < 0) {
		// Assume we start on white ground.
		// We have to throw away a few values at the start.
		if (brightness != 0 && ++white == 0) white = brightness;
		return 0;
	}
	int diff = white - brightness, bar = 0;
	if (diff < THRESHOLD) {
		// Currently on white ground.
		white = (9*white + brightness) / 10;
		if (state == BLACK) {
			// We just left a black bar.
			bar = 1;
		}
		state = WHITE;
	} else {
		state = BLACK;
	}
	/* print_tsv(3, brightness, white, state); */
	return bar;
}

int main() {
	unsigned int data[2];
	Init();
	FrontLED(ON);
	/* SetMotorPower(60, 60); */
	int bars = 0;
	while(1) {
		Msleep(20);
		LineData(data);
		if (next_brightness((data[0] + data[1]) / 2)) {
			SerPrint("------- ");
			PrintInt(++bars);
			SerPrint("\n");
		}
	}
	return 0;
}
