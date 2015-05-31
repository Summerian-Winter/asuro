#include <asuro.h>

// brightness: 0..1023, speed: -128..127
static int8_t brightness_to_speed(unsigned int brightness) {
	return (1024 - brightness) >> 3;
}

int main (void) {
	unsigned int data[2];
	Init();
	while(1) {
		LineData(data);
		SetMotorPower(
				brightness_to_speed(data[0]),
				brightness_to_speed(data[0]));
	}
}

