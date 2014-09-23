/*
 * Author: Letao Jiang
 * Login: jiang
 * ID: 720425082
 *
 * Honor code pledge: I finished this assginment by myself and did not get help from inappropriate way.
 *
 * This is a simple program that can take input from user and print lines with 80 characters
 *
 */

#include <stdlib.h>
#include <stdio.h>

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

void decideToPrint(int count, char * output) {
	if (count == MAX_LINE_SIZE) {
		printOutput(output, MAX_LINE_SIZE);
		count = 0;
	}
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
					decideToPrint(count, output);
					if (new == '\n' || new == '\r') {
						// replace the carriage return with space
						output[count++] = ' ';
					} else {
						output[count++] = new;
					}
				}
			} else {
				break;
			}
		} else {
			output[count++] = new;
		}
		decideToPrint(count, output);
		new = getchar();
	}
}
