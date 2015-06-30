#include "parcour.h"
#include <asuro.h>

bool has_hit_wall() {
	uint8_t t1, t2;
	t1 = PollSwitch(); Msleep(10); t2 = PollSwitch();
	// Ignore K6 while driving.
	return t1 && t1 == t2 && t1 & ~K6 && t1 < 64;
}

enum follow_result follow_wall(enum dir dir) {
	if (switched && has_hit_wall()) {
		switched = false;
		// We hit a wall. First, reverse.
		SetMotorPower(-BASE_SPEED * 2, -BASE_SPEED * 2);
		Msleep(100);
		// Continue in direction `dir`.
		if (dir == DIR_Left)
			SetMotorPower(-BASE_SPEED * 3 / 2, BASE_SPEED * 3 / 2);
		else if (dir == DIR_Right)
			SetMotorPower(BASE_SPEED * 3 / 2, -BASE_SPEED * 3 / 2);

		Msleep(180);
		return HIT_WALL;
	}
	if (dir == DIR_Left)
		SetMotorPower(BASE_SPEED * 4 / 3, BASE_SPEED);
	else if (dir == DIR_Right)
		SetMotorPower(BASE_SPEED, BASE_SPEED * 3 / 2);
	return NO_WALL;
}
