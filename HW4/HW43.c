/*
 * Author: Letao Jiang
 * Login: jiang
 * ID: 720425082
 *
 * Honor code pledge: I finished this assignment by myself and did not get help from inappropriate way.
 *
 * The asterisks processing function that will process the input and replace two * with ^.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ASTERISK '*'
#define CARET '^'
#define READ 0
#define WRITE 1

int main() {
  char c, tmp;
  read(READ, &c, sizeof(char)); /* read the character from the newline handler pipe*/
  while (c != EOF) {
    if (c == ASTERISK) {
      read(READ, &c, sizeof(char)); /* read the character from the newline handler pipe*/
      if (c != ASTERISK) {
        tmp = ASTERISK;
        write(WRITE, &tmp, sizeof(char)); /* write * to the output pipe*/
        write(WRITE, &c, sizeof(char)); /* write the character to the output pipe*/
      } else {
        tmp = CARET;
        write(WRITE, &tmp, sizeof(char)); /* write ^ to the output pipe*/
      }
      if (c == EOF) {
        break;
      }
    } else {
      write(WRITE, &c, sizeof(char)); /* write the character to the output pipe*/
    }
    read(READ, &c, sizeof(char));
  }
  write(WRITE, &c, sizeof(char)); /* write EOF to the output pipe*/
}
