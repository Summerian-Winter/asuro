#include <asuro.h>
#include "TimerService.h"

void print_message(void *data) {
	SerPrint((char*)data);
}

int main (void) {
	unsigned int data[2];
	Init();

	void *timer = add_timer(1000, print_message, "1s\n");
	add_timer(3000, print_message, "3s\n");
	add_timer(5000, print_message, "5s\n");
	add_timer(5000, remove_timer, timer);

	while(1) {
		Msleep(500);
	}
}

