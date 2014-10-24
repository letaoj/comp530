/*
 * Author: Letao Jiang
 * Login: jiang
 * ID: 720425082
 *
 * Honor code pledge: I finished this assignment by myself and did not get help from inappropriate way.
 *
 * The output function that output the line if it reaches 80 characters.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LINE_SIZE 80
#define NEWLINE '\n'
#define READ 0
#define WRITE 1

int main() {
  int count = 0;
  char c;
  char line[MAX_LINE_SIZE + 1];
  read(READ, &c, sizeof(char)); /* read the character from the output pipe*/
  while (c != EOF) {
    line[count] = c;
    count++;
    if (count == MAX_LINE_SIZE) {
      line[count] = '\0';
      printf("%s%c", line, NEWLINE);
      count = 0;
    }
    read(READ, &c, sizeof(char)); /* read the character from the output pipe*/
  }
}
