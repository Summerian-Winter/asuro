#include <asuro.h>
#include "parcour-lib/parcour.h"

int main() {
	Init();
	FrontLED(ON);

	search_line();
	do {
		while (!follow_line())
			Msleep(20);
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
