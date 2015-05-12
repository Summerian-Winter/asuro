#include "TimerService.h"
#include "asuro.h"
#include <stdbool.h>
#define MAX_TIMERS 5

struct _timer_entry {
	unsigned int duration;
	unsigned int current;
	timer_func func;
	void *data;
};

timer_entry timers[MAX_TIMERS];
bool did_init;

void init_timer() {
	TCCR0 = 0b011;
	TCNT0 = 130;
	TIMSK |= 1;
	did_init = true;
}

timer_entry* add_timer(unsigned int duration, timer_func func, void *data) {
	if (!did_init) init_timer();
	timer_entry *entry = NULL;
	for (int i = 0; i < MAX_TIMERS; i++) {
		if (timers[i].func == NULL) {
			entry = timers + i;
			break;
		}
	}
	if (entry == NULL) return NULL;
	entry->duration = duration;
	entry->current = 0;
	entry->func = func;
	entry->data = data;
	return entry;
}

void remove_timer(timer_entry *timer) {
	timer->func = NULL;
}

ISR(TIMER0_OVF_vect, ISR_NOBLOCK) {
	for (int i = 0; i < MAX_TIMERS; i++) {
		if (timers[i].func && ++timers[i].current == timers[i].duration) {
			timers[i].func(timers[i].data);
			timers[i].current = 0;
		}
	}
	init_timer();
}
