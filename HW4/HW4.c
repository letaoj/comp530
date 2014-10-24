/*
 * Author: Letao Jiang
 * Login: jiang
 * ID: 720425082
 *
 * Honor code pledge: I finished this assignment by myself and did not get help from inappropriate way.
 *
 * This is a multi-process program derived from HW1 that can take input from user and print lines with 80 characters
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define ASTERISK '*'
#define BLANK ' '
#define CARET '^'
#define CARRIAGE '\r'
#define MAX_LINE_SIZE 80
#define NEWLINE '\n'
#define READ 0
#define WRITE 1

// Method signature
void input_process();
void carriage_processing_process();
void asterisks_processing_process();
void output_process();

/*
 * Main function that will create all the process for processing the input
 */
int main() {

  // pipes that used to pass the data
  int input_pipe[2];
  int carriage_handler_pipe[2];
  int asterisk_handler_pipe[2];

  // Children pid
  pid_t carriage_process_pid;
  pid_t asterisks_process_pid;
  pid_t output_pid;

  // create pipes to connect processes
  if (pipe(input_pipe) == -1) {
    perror("creating input pipe");
    exit(1);
  }
  if (pipe(carriage_handler_pipe) == -1) {
    perror("creating newline handler pipe");
    exit(1);
  }
  if (pipe(asterisk_handler_pipe) == -1) {
    perror("creating asterisk handler pipe");
    exit(1);
  }

  // fork the chile processes
  if ((carriage_process_pid = fork()) == -1) {
    perror("fork carriage processing");
    exit(1);
  }
  if (carriage_process_pid != 0) {  // parent process
    close(input_pipe[READ]);
    input_process(input_pipe[WRITE]);
    wait(&carriage_process_pid);
  } else {  // chile process
    if ((asterisks_process_pid = fork()) == -1) {
      perror("fork asterisks processing");
      exit(1);
    }
    if (asterisks_process_pid != 0) {  // parent process
      close(input_pipe[WRITE]);
      close(carriage_handler_pipe[READ]);
      carriage_processing_process(input_pipe[READ],
                                  carriage_handler_pipe[WRITE]);
      wait(&asterisks_process_pid);
    } else {  // child process
      if ((output_pid = fork()) == -1) {
        perror("fork output");
        exit(1);
      }
      if (output_pid != 0) {  // parent process
        close(carriage_handler_pipe[WRITE]);
        close(asterisk_handler_pipe[READ]);
        asterisks_processing_process(carriage_handler_pipe[READ],
                                     asterisk_handler_pipe[WRITE]);
        wait(&output_pid);
      } else {  // child process
        close(asterisk_handler_pipe[WRITE]);
        output_process(asterisk_handler_pipe[READ]);
      }
    }
  }
  return 0;
}

/**
 * The input process function that will read from the stdin and write to input pipe
 */
void input_process(int write_descriptor) {
  char c;

  do {
    c = getchar();
    if (c != EOF) {
      write(write_descriptor, &c, sizeof(char)); /* write the character to the input pipe*/
    }
  } while (c != EOF);
  write(write_descriptor, &c, sizeof(char)); /* write EOF to the input pipe*/
}

/**
 * The carriage processing function that will process the input
 * and get rid of the carriage character
 */
void carriage_processing_process(int read_descriptor, int write_descriptor) {
  char c;
  read(read_descriptor, &c, sizeof(char)); /* read the character from the input pipe*/
  while (c != EOF) {
    if (c == NEWLINE || c == CARRIAGE) {
      c = BLANK;
    }
    write(write_descriptor, &c, sizeof(char)); /* write the character to the newline handler pipe*/
    read(read_descriptor, &c, sizeof(char)); /* read the character from the input pipe*/
  }
  write(write_descriptor, &c, sizeof(char)); /* write EOF to the newline handler pipe*/
}

/**
 * The asterisks processing function that will process the input and replace two * with ^.
 */
void asterisks_processing_process(int read_descriptor, int write_descriptor) {
  char c, tmp;
  read(read_descriptor, &c, sizeof(char)); /* read the character from the newline handler pipe*/
  while (c != EOF) {
    if (c == ASTERISK) {
      read(read_descriptor, &c, sizeof(char)); /* read the character from the newline handler pipe*/
      if (c != ASTERISK) {
        tmp = ASTERISK;
        write(write_descriptor, &tmp, sizeof(char)); /* write * to the output pipe*/
        write(write_descriptor, &c, sizeof(char)); /* write the character to the output pipe*/
      } else {
        tmp = CARET;
        write(write_descriptor, &tmp, sizeof(char)); /* write ^ to the output pipe*/
      }
      if (c == EOF) {
        break;
      }
    } else {
      write(write_descriptor, &c, sizeof(char)); /* write the character to the output pipe*/
    }
    read(read_descriptor, &c, sizeof(char));
  }
  write(write_descriptor, &c, sizeof(char)); /* write EOF to the output pipe*/
}

/**
 * The output function that output the line if it reaches 80 characters.
 */
void output_process(int read_descriptor) {
  int count = 0;
  char c;
  char line[MAX_LINE_SIZE + 1];
  read(read_descriptor, &c, sizeof(char)); /* read the character from the output pipe*/
  while (c != EOF) {
    line[count] = c;
    count++;
    if (count == MAX_LINE_SIZE) {
      line[count] = '\0';
      printf("%s%c", line, NEWLINE);
      count = 0;
    }
    read(read_descriptor, &c, sizeof(char)); /* read the character from the output pipe*/
  }
}

