#include <asuro.h>
#include "TimerService.h"

void read_data(void *_data) {
	static int time = 0;

	unsigned int data[2];
	OdometryData(data);

	PrintInt(time++);      SerPrint(",");
	PrintInt(data[LEFT]);  SerPrint(",");
	PrintInt(data[RIGHT]); SerPrint("\n");
}

int main (void) {
	Init();

	SerPrint("time,left,right\n");
	add_timer(100, read_data, NULL);

	while(1) {
		Msleep(500);
	}
}

