#include "semaphore.h"

#define MAX_LINE_SIZE 80

//buffer struct
typedef struct {
	int nextIn;
	int nextOut;
	char chars[MAX_LINE_SIZE];
	semaphore emptyBuffer;
	semaphore fullBuffer;
} buffer;

// This function deposit a character into the buffer.
void deposit(buffer* buff, char c);
// This function remove the first character in the buffer and let the buffer point to the next one
char remoove(buffer* buff);
// This function create and initialized the buffer
void createBuffer(buffer* buff);
