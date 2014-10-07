/*
 * Re-implementation of semaphore
 */

#include "semaphore.h"

// Busy waiting
void down(semaphore *s) {
	while (s->value == 0) {
		st_cond_wait(s->sem_queue);
	}
	s->value--;
}

void up(semaphore *s) {
	s->value++;
	st_cond_signal(s->sem_queue);
}

// create and initialize the semaphore
void createSem(semaphore *s, int value) {
	s->value = value;
	s->sem_queue = st_cond_new();
}
