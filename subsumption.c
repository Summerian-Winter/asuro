#include <asuro.h>

static void avoid_collision() {
	uint8_t t1, t2;
	t1 = PollSwitch(); t2 = PollSwitch();
	// Ignore K6 while driving.
	while (t1 && t1 == t2 && t1 & ~K6 && t1 < 64) {
		SerPrint("Collision: "); PrintInt(t1);
		// Stop to get better values.
		MotorSpeed(0, 0);
		Msleep(100);

		t1 = PollSwitch(); t2 = PollSwitch();
		SerPrint(" "); PrintInt(t1); SerPrint("\n");

		uint8_t speedl = 0, speedr = 0;
		if (t1 & K1) speedl -= 10;
		if (t1 & K2) speedl -= 10;
		if (t1 & K3) speedl -= 10;
		if (t1 & K4) speedr -= 10;
		if (t1 & K5) speedr -= 10;
		if (t1 & K6) speedr -= 10;
		MotorSpeed(speedl, speedr);

		Msleep(500);
		t1 = PollSwitch(); t2 = PollSwitch();
	}
}

// brightness: 0..1023, speed: -128..127
static int8_t brightness_to_speed(unsigned int brightness) {
	return (1024 - brightness) >> 3;
}

static void search_light() {
	unsigned int data[2];
	LineData(data);
	SetMotorPower(
			brightness_to_speed(data[0]),
			brightness_to_speed(data[0]));
}

int main (void) {
	Init();
	while(1) {
		avoid_collision();
		search_light();
	}
}

