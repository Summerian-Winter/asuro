#include <asuro.h>

#include "avoid_collision.h"

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

