/*
 * Author: Letao Jiang
 * Login: jiang
 * ID: 720425082
 *
 * Honor code pledge: I finished this assginment by myself and did not get help from inappropriate way.
 *
 * This is a multi-thread program derived from HW1 that can take input from user and print lines with 80 characters
 *
 */

// Standard includes
#include <stdlib.h>
#include <stdio.h>

// Library and custom includes
#include "buffer.h"

// Output-related defaults (stream, message, shared value length)
#define MAX_LINE_SIZE 80
#define ASTERISK '*'
#define CARET '^'
#define BLANK ' '
#define NEWLINE '\n'
#define CARRIAGE '\r'

typedef struct {
	buffer *in;
	buffer *out;
} ThreadInit;

// Method signature
void *input_thread(void *state);
void *carriage_processing_thread(void *state);
void *asterisks_processing_thread(void *state);
void *output_thread(void *state);

int main() {
	//malloc all the buffers
	buffer input_buffer;
	buffer newline_handler_buffer;
	buffer asterisk_handler_buffer;

	// create and initiate the buffers
	createBuffer(&input_buffer);
	createBuffer(&newline_handler_buffer);
	createBuffer(&asterisk_handler_buffer);

	// create the initiate state for each thread
	ThreadInit input_thread_init = { NULL, &input_buffer };
	ThreadInit carriage_processing_thread_init = { &input_buffer,
			&newline_handler_buffer };
	ThreadInit asterisks_processing_thread_init = { &newline_handler_buffer,
			&asterisk_handler_buffer };
	ThreadInit output_thread_init = { &asterisk_handler_buffer, NULL };

	// Initialize the libST runtime.
	st_init();

	//create a thread for reading input
	if (st_thread_create(input_thread, &input_thread_init, 0, 0) == NULL) {
		perror("failed to create input thread");
		exit(1);
	}

	//create a thread for replacing the carriage returns with blanks
	if (st_thread_create(carriage_processing_thread,
			&carriage_processing_thread_init, 0, 0) == NULL) {
		perror("failed to create processing carriage thread");
		exit(1);
	}

	//create a thread for processing asterisks
	if (st_thread_create(asterisks_processing_thread,
			&asterisks_processing_thread_init, 0, 0) == NULL) {
		perror("failed to create processing asterisks thread");
		exit(1);
	}

	//create a thread for writing output
	if (st_thread_create(output_thread, &output_thread_init, 0, 0) == NULL) {
		perror("failed to create output thread");
		exit(1);
	}

	// Exit from main via ST.
	st_thread_exit(NULL);

	return 0;
}

void *input_thread(void *state) {
	ThreadInit *init = state;
	char c;

	while ((c = getchar()) != EOF) {
		deposit(init->out, c);
	}
	deposit(init->out, c);
	// Exit from main via ST.
	st_thread_exit(NULL);

	// get rid of the warning
	return NULL;
}

void *carriage_processing_thread(void *state) {
	ThreadInit *init = (ThreadInit *) state;
	char c;
	while ((c = remoove(init->in)) != EOF) {
		if (c == NEWLINE || c == CARRIAGE) {
			c = BLANK;
		}
		deposit(init->out, c);
	}
	deposit(init->out, c);
	// Exit from main via ST.
	st_thread_exit(NULL);

	// get rid of the warning
	return NULL;
}

void *asterisks_processing_thread(void *state) {
	ThreadInit *init = state;
	char c;

	while ((c = remoove(init->in)) != EOF) {
		if (c == ASTERISK) {
			c = remoove(init->in);
			if (c != ASTERISK) {
				deposit(init->out, ASTERISK);
				deposit(init->out, c);
			} else {
				deposit(init->out, CARET);
			}
			if (c == EOF) {
				st_thread_exit(NULL);
			}
		} else {
			deposit(init->out, c);
		}
	}
	deposit(init->out, c);
	// Exit from main via ST.
	st_thread_exit(NULL);

	// get rid of the warning
	return NULL;
}

void *output_thread(void *state) {
	ThreadInit *init = state;
	int count = 0;
	char c;
	char line[MAX_LINE_SIZE + 1];

	while ((c = remoove(init->in)) != EOF) {
		line[count] = c;
		if (count == MAX_LINE_SIZE - 1) {
			line[MAX_LINE_SIZE] = '\0';
			printf("%s\n", line);
			count = 0;
		} else {
			count++;
		}
	}

	// Exit from main via ST and free pointer.
	st_thread_exit(NULL);

	// get rid of the warning
	return NULL;
}
