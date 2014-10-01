#include "semaphore.h"
#define MAX_LINE_SIZE 80

//this function takes in a semaphore pointer, and synchronize when the value of semaphore is 0.
void down(semaphore *s) {
	//wait if value of semaphore is 0.
	while (s->value == 0) {
		st_cond_wait(s->sem_queue);
	}
	//decrement semaphore's value
	s->value -= 1;
}

//this function takes in a semaphore pointer, increment semaphore's value and signal semaphore's value > 0
void up(semaphore *s) {
	//increment semaphore's value
	s->value += 1;
	//signal semaphore's value > 0, so the waiting process can proceed
	st_cond_signal(s->sem_queue);
}

//this function init a semaphore
void createSem(semaphore *s, int value) {
	s->value = value;
	//create a new conditional variable
	s->sem_queue = st_cond_new();
}
