#include <math.h>
#include "asuro.h"

#define THRESHOLD 200

static int bars = 0;

// brightness: 0..1023
static int next_brightness(int brightness) {
	static int prev = 0, change = 0;
	static char dir = 0;
	if (dir == 0) goto out;
	if (abs(prev - brightness) < THRESHOLD) goto out;
	char next_dir = prev < brightness ? 1 : -1;
	if (next_dir != dir) {
		bars++;
		dir = next_dir;
		change = 1;
	}
out:
	prev = brightness;
	return change;
}

int main() {
	unsigned int data[2];
	Init();
	FrontLED(ON);
	SetMotorPower(60, 60);
	while(1) {
		LineData(data);
		if (next_brightness((data[0] + data[1]) / 2)) {
			SerPrint("------- ");
			PrintInt(bars);
			SerPrint("\n");
			if (bars > 3) {
				SetMotorPower(0, 0);
				break;
			}
		}
	}
	return 0;
}
