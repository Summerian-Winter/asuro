#include <math.h>
#include "asuro.h"

#define THRESHOLD 100

// brightness: 0..1023
static int next_brightness(int left, int right) {
	// Assume we are (mostly) on the line.

	// ~same data from both sensors -> go straight.
	if (abs(left - right) < THRESHOLD)
		return 0;
	// More light on the right -> correct to the left.
	if (left < right)
		return -10; // TODO: Adaptive correction?
	else // More light on the left.
		return 10;
}

int main() {
	unsigned int data[2];
	Init();
	FrontLED(ON);
	const int base_speed = 50;
	SetMotorPower(base_speed, base_speed);
	int diff;
	while(1) {
		Msleep(20);
		LineData(data);
		diff = next_brightness(data[0], data[1]);
		SetMotorPower(base_speed + diff, base_speed - diff);
	}
	return 0;
}
