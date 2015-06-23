#pragma once
#include <stdbool.h>

#define BASE_SPEED 35

// Wall following
enum dir { DIR_Left, DIR_Right };
enum follow_result { HIT_WALL, NO_WALL };
enum follow_result follow_wall(enum dir dir);

// Line following
void search_line();
void follow_line();
bool check_line_end();

// Bar counting
int count_bar();
