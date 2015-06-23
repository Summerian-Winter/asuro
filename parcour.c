#include <asuro.h>
#include "parcour-lib/parcour.h"

enum state {
	SEARCH_LINE,
	FOLLOW_LINE,
	FOLLOW_WALL,
	/* COUNT_BARS, */
};

int main (void) {
	enum state state = SEARCH_LINE;
	Init();
	FrontLED(ON);
	SetMotorPower(BASE_SPEED, BASE_SPEED);
	while(1) {
		switch (state) {
		case SEARCH_LINE:
			search_line();
			state = FOLLOW_LINE;
		case FOLLOW_LINE:
			if (!follow_line()) {
				break;
			}
			if (check_line_end())
				state = FOLLOW_WALL;
			else
				state = FOLLOW_LINE;
			break;
		case FOLLOW_WALL:
			if (follow_wall(DIR_Right) == NO_WALL) {
				if (is_on_line()) {
					state = FOLLOW_LINE;
					break;
				}
			}
			SetMotorPower(BASE_SPEED, BASE_SPEED);
			Msleep(100);
			break;
		}
	}
}
