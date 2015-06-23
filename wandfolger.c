#include <asuro.h>
#include "parcour-lib/parcour.h"

int main (void) {
	Init();
	SetMotorPower(BASE_SPEED, BASE_SPEED);
	while(1) {
		if (follow_wall(DIR_Right) == HIT_WALL) {
			// Continue onwards.
			SetMotorPower(BASE_SPEED, BASE_SPEED);
		}
		Msleep(100);
	}
}
