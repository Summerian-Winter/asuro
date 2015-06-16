#include <math.h>
#include <stdbool.h>
#include "asuro.h"

// Number of ~20ms ticks for turning 90deg.
#define TICKS_FOR_90_DEG 20
// Maximum brightness distance for colors assumed to be equal.
#define SAME_COLOR_THRESHOLD 100
// Absolute threshold for black/white.
#define BLACK_THRESHOLD 500
// Motor speed.
#define BASE_SPEED 35

// Returns true if at least one sensor is on black.
static bool on_black() {
	unsigned int data[2];
	LineData(data);
	// Discard invalid values.
	if (data[0] == 0 || data[1] == 0) return false;
	return data[0] < BLACK_THRESHOLD || data[1] < BLACK_THRESHOLD;
}

static void search_line() {
	SetMotorPower(-BASE_SPEED, BASE_SPEED);
	while (1) {
		Msleep(20);
		if (on_black()) return;
	}
}

// brightness: 0..1023
static int brightness_to_speed_diff(int left, int right) {
	// Assume we are (mostly) on the line.

	// ~same data from both sensors -> go straight.
	if (abs(left - right) < SAME_COLOR_THRESHOLD)
		return 0;
	// More light on the right -> correct to the left.
	if (left < right)
		return -BASE_SPEED;
	else // More light on the left.
		return BASE_SPEED;
}

static void follow_line() {
	unsigned int data[2];
	const int base_speed = BASE_SPEED;
	int diff;
	while(1) {
		Msleep(20);
		LineData(data);
		diff = brightness_to_speed_diff(data[0], data[1]);
		if (diff)
			SetMotorPower(+diff, -diff);
		else
			SetMotorPower(base_speed, base_speed);

		if (!on_black()) return;
	}
}

static bool check_line_end() {
	int ticks;
	SetMotorPower(-BASE_SPEED, BASE_SPEED);
	ticks = TICKS_FOR_90_DEG;
	while (ticks--) {
		if (on_black()) return false;
		Msleep(20);
	}
	SetMotorPower(BASE_SPEED, -BASE_SPEED);
	ticks = 2 * TICKS_FOR_90_DEG;
	while (ticks--) {
		if (on_black()) return false;
		Msleep(20);
	}
	return true; // end reached
}

int main() {
	Init();
	FrontLED(ON);

	search_line();
	do {
		follow_line();
	} while (!check_line_end());

	SetMotorPower(0, 0);
	while (1) {
		BackLED(ON, ON);
		Msleep(100);
		BackLED(OFF, OFF);
		Msleep(100);
	}

	return 0;
}
