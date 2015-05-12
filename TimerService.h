#ifndef TIMER_SERVICE_H
#define TIMER_SERVICE_H

typedef void (*timer_func)(void *data);
struct _timer_entry;
typedef struct _timer_entry timer_entry;

timer_entry* add_timer(unsigned int duration, timer_func func, void *data);
void remove_timer(timer_entry *timer);

#endif
