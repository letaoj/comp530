/*
 * I finished this assginment under then honor code and I did not share my
 * code with others.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "warmup.h"

#define MAX_LINE_SIZE 80

/*
 * Help method that takes a char array and its length as parameter
 * and print out the whole array.
 *
 */
void printOutput(char output[], int length) {
	int i;
	int l = length < MAX_LINE_SIZE ? length : MAX_LINE_SIZE;
	for (i = 0; i < l; i++) {
		printf("%c", output[i]);
	}
	printf("\n");
}

int main() {
	int count = 0;
	char output[MAX_LINE_SIZE];
	int new = getchar();
	while (new != EOF) // while not meet the end of file char
	{
		if (new == '\n' || new == '\r') {
			// replace the carriage return with space
			output[count++] = ' ';
		} else if (new == '*') {
			// handler the case,  where we encounted a * char
			new = getchar();
			if (new != EOF) {
				if (new == '*') {
					output[count++] = '^';
				} else {
					output[count++] = '*';
					if (count == MAX_LINE_SIZE) {
						printOutput(output, MAX_LINE_SIZE);
						count = 0;
					}
					if (new == '\n' || new == '\r') {
						// replace the carriage return with space
						output[count++] = ' ';
					} else {
						output[count++] = new;
					}
				}
			}
		} else {
			output[count++] = new;
		}
		if (count == MAX_LINE_SIZE) {
			// counted max number allowed in a line, print it
			printOutput(output, MAX_LINE_SIZE);
			count = 0;
		}
		new = getchar();
	}
}
