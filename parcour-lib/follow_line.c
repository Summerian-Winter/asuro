#include <math.h>
#include "asuro.h"
#include "parcour.h"

// Number of ~20ms ticks for turning 90deg.
#define TICKS_FOR_90_DEG 23
#define TICKS_FOR_180_DEG 35
// Maximum brightness distance for colors assumed to be equal.
#define SAME_COLOR_THRESHOLD 100
// Absolute threshold for black/white.
#define BLACK_THRESHOLD 500

// Returns true if at least one sensor is on black.
static bool on_black() {
	unsigned int data[2];
	LineData(data);
	// Discard invalid values.
	if (data[0] == 0 || data[1] == 0) return false;
	return data[0] < BLACK_THRESHOLD || data[1] < BLACK_THRESHOLD;
}

bool is_on_line() { return on_black(); }

// Search for a line somewhere in front of Asuro.
void search_line() {
	int ticks;

#define TICKS_LOOP \
	while (ticks--) { \
		if (on_black()) return; \
		Msleep(20); \
	}

	while (1) {
		// Look on the left.
		SetMotorPower(-BASE_SPEED, BASE_SPEED);
		ticks = TICKS_FOR_90_DEG;
		TICKS_LOOP;
		// Look on the right.
		SetMotorPower(BASE_SPEED, -BASE_SPEED);
		ticks = TICKS_FOR_180_DEG;
		TICKS_LOOP;
		// Go back.
		SetMotorPower(-BASE_SPEED, BASE_SPEED);
		ticks = TICKS_FOR_90_DEG;
		TICKS_LOOP;
		// Go straight.
		SetMotorPower(BASE_SPEED, BASE_SPEED);
		ticks = 20;
		TICKS_LOOP;
	}
#undef TICKS_LOOP
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

// Returns true when the line is lost.
bool follow_line() {
	unsigned int data[2];
	const int base_speed = BASE_SPEED;
	int diff;

	Msleep(20);
	LineData(data);
	diff = brightness_to_speed_diff(data[0], data[1]);
	if (diff)
		SetMotorPower(+diff, -diff);
	else
		SetMotorPower(base_speed, base_speed);

	if (!on_black()) return true;
	return false;
}

bool check_line_end() {
	int ticks;
	SetMotorPower(-BASE_SPEED, BASE_SPEED);
	ticks = TICKS_FOR_90_DEG;
	while (ticks--) {
		if (on_black()) return false;
		Msleep(20);
	}
	SetMotorPower(BASE_SPEED, -BASE_SPEED);
	ticks = TICKS_FOR_180_DEG;
	while (ticks--) {
		if (on_black()) return false;
		Msleep(20);
	}
	return true; // end reached
}
