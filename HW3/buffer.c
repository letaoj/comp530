/*
 * implemtation of bounded buffer
 */

// Standard includes
#include <stdlib.h>
#include <stdio.h>

// Library and custom includes
#include "buffer.h"
#include "st.h"

// Follow the producer's pseudocode, use semaphore to ensure the correctness of critical section
void deposit(buffer* buf, char c) {
	down(&(buf->emptyBuffer));

	// critical section
	buf->chars[buf->nextIn] = c;
	buf->nextIn = (buf->nextIn + 1) % MAX_LINE_SIZE;

	up(&(buf->fullBuffer));
}

// Follow the consumer's pseudocode, use semaphore to ensure the correctness of critical section
char remoove(buffer* buf) {
	down(&(buf->fullBuffer));

	// critical section
	char c = buf->chars[buf->nextOut];
	buf->nextOut = (buf->nextOut + 1) % MAX_LINE_SIZE;

	up(&(buf->emptyBuffer));
	return c;
}

// Create and initialized the buffer
void createBuffer(buffer* buf) {
	buf->nextIn = 0;
	buf->nextOut = 0;
	buf->chars[0] = '\0';
	createSem(&(buf->emptyBuffer), MAX_LINE_SIZE);
	createSem(&(buf->fullBuffer), 0);
}
