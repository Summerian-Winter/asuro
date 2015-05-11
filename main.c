#include <asuro.h>

int main (void) {
	unsigned int data[2];
	Init();
	while(1) {
		LineData(data);
		PrintInt(data[LEFT]);
		SerPrint("\n");
		PrintInt(data[RIGHT]);
		SerPrint("\n\n\n");
		Msleep(500);
	}
}

