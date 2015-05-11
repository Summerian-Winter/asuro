#ifndef TIMER_SERVICE_H
#define TIMER_SERVICE_H

typedef void (*timer_func)(void *data);
typedef struct {
	unsigned int duration;
	unsigned int current;
	timer_func func;
	void *data;
} timer_entry;

timer_entry* add_timer(unsigned int duration, void *data);
void remove_timer(timer_entry *timer);

#endif
