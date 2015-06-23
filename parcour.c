#include <asuro.h>
#include "parcour-lib/parcour.h"

enum state {
	SEARCH_LINE,
	FOLLOW_LINE,
	FOLLOW_WALL,
	COUNT_BARS,
	STOP
};

int main (void) {
	enum state state = SEARCH_LINE;
	int bars = 0;
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
				if (has_hit_wall())
					state = FOLLOW_WALL;
				else
					Msleep(10);
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
		case COUNT_BARS:
			if (count_bar()) {
				// Stop after three bars.
				if (++bars == 3)
					state = STOP;
			}
			break;
		case STOP:
			while (1) {
				BackLED(ON, ON);
				Msleep(100);
				BackLED(OFF, OFF);
				Msleep(100);
			}
		}
	}
}
