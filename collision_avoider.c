#include <asuro.h>

int main (void) {
	uint8_t t1, t2;
	int8_t speedl, speedr;
	Init();
	while(1) {
		t1 = PollSwitch(); t2 = PollSwitch();
		if (t1 && t1 == t2) {
			// base speed
			speedl = 64; speedr = 64;
			if (t1 & K1) speedl -= 32;
			if (t1 & K2) speedl -= 32;
			if (t1 & K3) speedl -= 32;
			if (t1 & K4) speedr -= 32;
			if (t1 & K5) speedr -= 32;
			if (t1 & K6) speedr -= 32;
			SetMotorPower(speedl, speedr);
		}
	}
}


