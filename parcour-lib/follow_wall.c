#include "parcour.h"
#include <asuro.h>

bool has_hit_wall() {
	uint8_t t1, t2;
	t1 = PollSwitch(); Msleep(10); t2 = PollSwitch();
	// Ignore K6 while driving.
	return t1 && t1 == t2 && t1 & ~K6 && t1 < 64;
}

enum follow_result follow_wall(enum dir dir) {
	if (has_hit_wall()) {
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
