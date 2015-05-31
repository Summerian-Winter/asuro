#include <asuro.h>
#include <stdbool.h>
#include "TimerService.h"

#define speed 100

static int l_speed = speed, r_speed = speed;
static volatile bool go = true;

static void correct_motor_diff() {
    int diff = encoder [LEFT] - encoder [RIGHT];

    if (diff > 0)
    { /* Left faster than right */
      if ((l_speed > speed) || (r_speed > 244))
        l_speed -= 10;
      else
        r_speed += 10;
    }

    if (diff < 0)
    { /* Right faster than left */
      if ((r_speed > speed) || (l_speed > 244))
        r_speed -= 10;
      else
        l_speed += 10;
    }
}

static uint8_t switch_pressed() {
	uint8_t t1, t2;
	t1 = PollSwitch();
	t2 = PollSwitch();
	if (t1 && t1 == t2) {
		PrintInt(t1);
		return t1;
	}
	return 0;
}

static void check_switch(void *foo) {
	if (switch_pressed() > 1) {
		go = false;
	}
}

int main (void) {
	Init();
	EncoderInit();

	add_timer(100, check_switch, NULL);

	MotorDir(FWD, FWD);

	int count[2] = {0, 0};

	do {
		EncoderSet(0, 0);
		MotorSpeed(l_speed, r_speed);

		Msleep(1);

		count[LEFT] += encoder[LEFT];
		count[RIGHT] += encoder[RIGHT];
		correct_motor_diff();
		EncoderSet(0, 0);

	} while (go);

	MotorSpeed(0, 0);
	while (1) {
		SerPrint("LEFT: ");
		PrintInt(count[LEFT]);
		SerPrint(" RIGHT: ");
		PrintInt(count[RIGHT]);
		SerPrint("\n");
		Msleep(1000);
	}
}

