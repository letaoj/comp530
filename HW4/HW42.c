/*
 * Author: Letao Jiang
 * Login: jiang
 * ID: 720425082
 *
 * Honor code pledge: I finished this assignment by myself and did not get help from inappropriate way.
 *
 * The carriage processing function that will process the input and get rid of the carriage character
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BLANK ' '
#define CARRIAGE '\r'
#define NEWLINE '\n'
#define READ 0
#define WRITE 1

int main() {
  char c;
  read(READ, &c, sizeof(char)); /* read the character from the input pipe*/
  while (c != EOF) {
    if (c == NEWLINE || c == CARRIAGE) {
      c = BLANK;
    }
    write(WRITE, &c, sizeof(char)); /* write the character to the newline handler pipe*/
    read(READ, &c, sizeof(char)); /* read the character from the input pipe*/
  }
  write(WRITE, &c, sizeof(char)); /* write EOF to the newline handler pipe*/
}
