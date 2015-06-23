#include <asuro.h>

#define BASE_SPEED 35

enum { DIR_Left, DIR_Right };
enum { HIT_WALL, NO_WALL };

static int follow_wall(int dir) {
	uint8_t t1, t2;
	t1 = PollSwitch(); Msleep(10); t2 = PollSwitch();
	// Ignore K6 while driving.
	if (t1 && t1 == t2 && t1 & ~K6 && t1 < 64) {
		// We hit a wall. Continue in direction `dir`.
		if (dir == DIR_Left)
			SetMotorPower(-BASE_SPEED * 2, -BASE_SPEED);
		else if (dir == DIR_Right)
			SetMotorPower(-BASE_SPEED, -BASE_SPEED * 2);

		Msleep(200);
		return HIT_WALL;
	}
	return NO_WALL;
}

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
