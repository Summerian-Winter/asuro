#include <asuro.h>

#include "avoid_collision.h"

int main (void) {
	int8_t speedl, speedr;
	Init();
	while(1) {
		avoid_collision();

		// base speed
		speedl = 64; speedr = 64;
		SetMotorPower(speedl, speedr);
	}
}


