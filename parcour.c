#include <asuro.h>
#include "parcour-lib/parcour.h"

enum state {
	SEARCH_LINE,
	START_FOLLOW_LINE,
	FOLLOW_LINE,
	START_FOLLOW_WALL,
	FOLLOW_WALL,
	START_COUNT_BARS,
	COUNT_BARS,
	STOP
};

int main (void) {
	enum state state = START_FOLLOW_LINE;
	int bars = 0, hits = 0;
	Init();
	StartSwitch();
	FrontLED(ON);
	SetMotorPower(BASE_SPEED, BASE_SPEED);
	while(1) {
		switch (state) {
		case SEARCH_LINE:
			search_line();
		case START_FOLLOW_LINE:
			state = FOLLOW_LINE;
			BackLED(ON, OFF);
		case FOLLOW_LINE:
			if (has_hit_wall()) {
				state = START_FOLLOW_WALL;
				break;
			}
			if (!follow_line()) {
				Msleep(10);
				break;
			}
			if (check_line_end())
				state = START_COUNT_BARS;
			else
				state = FOLLOW_LINE;
			break;
		case START_FOLLOW_WALL:
			switched = true;
			state = FOLLOW_WALL;
			BackLED(OFF, ON);
		case FOLLOW_WALL: // Follow to the right
			if (follow_wall(DIR_Right) == NO_WALL) {
				if (is_on_line()) {
					state = START_FOLLOW_LINE;
					break;
				}
			}
			break;
		case START_COUNT_BARS:
			bars = 0;
			state = COUNT_BARS;
			BackLED(ON, ON);
		case COUNT_BARS:
			SetMotorPower(BASE_SPEED, BASE_SPEED);
			if (has_hit_wall()) {
				state = START_FOLLOW_WALL;
				break;
			}
			if (count_bar()) {
				// Stop after three bars.
				if (++bars == 3)
					state = STOP;
			}
			break;
		case STOP:
			SetMotorPower(0, 0);
			while (1) {
				BackLED(ON, ON);
				Msleep(100);
				BackLED(OFF, OFF);
				Msleep(100);
			}
		}
	}
}
