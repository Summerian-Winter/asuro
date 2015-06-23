#include <math.h>
#include <asuro.h>
#include "parcour-lib/parcour.h"


int main() {
	Init();
	FrontLED(ON);
	SetMotorPower(50, 50);
	int bars = 0;
	while(1) {
		Msleep(20);
		if (count_bar()) {
			SerPrint("------- ");
			PrintInt(++bars);
			SerPrint("\n");
		}
	}
	return 0;
}
