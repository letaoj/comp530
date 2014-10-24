/*
 * Author: Letao Jiang
 * Login: jiang
 * ID: 720425082
 *
 * Honor code pledge: I finished this assignment by myself and did not get help from inappropriate way.
 *
 * The input process function that will read from the stdin and write to stdout
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main() {
  char c;

  do {
    c = getchar();
    if (c != EOF) {
      write(WRITE, &c, sizeof(char)); /* write the character to the input pipe*/
    }
  } while (c != EOF);
  write(WRITE, &c, sizeof(char)); /* write EOF to the input pipe*/

}
