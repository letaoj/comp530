/*
 * I finished this assginment under then honor code and I did not share my
 * code with others.
 *
 */

/*
 *  A basic shell can read from standard input, parse the input and execute the command.
 *
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_FILENAME_LENGTH (64 << 10)
#define MAX_NUMBER_OF_PARAMETERS 2048

/*
 * signal handler for SIGINT
 *
 */
void sigint() {
	printf("\n");
	signal(SIGINT, SIG_IGN);
}

/*
 * signal handler for SIGTSTP
 *
 */
void sigtstp() {
	printf("\n");
	signal(SIGTSTP, SIG_IGN);
}

/*
 * helper function to find the full path of a give filename
 *
 */
char * findpath(char * env, char * filename) {
	char * full_path;
	char * token = strtok(env, ":");
	struct stat sb;
	full_path = malloc(sizeof(char) * (strlen(token) + strlen(filename) + 1));
	strcpy(full_path, token);
	strcat(full_path, "/");
	strcat(full_path, filename);

	while ((token = strtok(NULL, ":"))) {
		if (stat(full_path, &sb) == -1) {
			full_path = realloc(full_path,
					sizeof(char) * (strlen(token) + strlen(filename) + 1));
			strcpy(full_path, token);
			strcat(full_path, "/");
			strcat(full_path, filename);
		} else {
			return full_path;
		}
	}
	return NULL;
}

/*
 * print out the %
 *
 */
void print_prompt() {
	printf("%% ");
	fflush(stdout);
}

int main() {
	size_t buf_len = 10;
	size_t read_len;
	pid_t childPid;
	struct stat s;

	print_prompt();

	char * line = (char *) malloc(sizeof(char) * buf_len);
	while ((read_len = getline(&line, &buf_len, stdin)) != -1) {
		line[read_len - 1] = '\0'; // remove the new line at the end

		childPid = fork(); // create a child process

		if (childPid == 0) {
			char * token;
			char filename[MAX_FILENAME_LENGTH];
			char * args[MAX_NUMBER_OF_PARAMETERS];
			int i = 0;

			// extract the filename from the input
			token = strtok(line, " ");
			if (strlen(token) > MAX_FILENAME_LENGTH) {
				fprintf(stderr, "Filename length exceed the maximum length\n");
				exit(1);
			}
			strncpy(filename, token, MAX_FILENAME_LENGTH);

			// parse the args from input
			args[i++] = filename;
			while ((token = strtok(NULL, "")) && i < MAX_NUMBER_OF_PARAMETERS) {
				args[i++] = token;
			}
			args[i] = NULL;

			char * full_path = findpath(getenv("PATH"), filename);
			if (full_path == NULL) {
				if (stat(filename, &s) != -1) {
					printf("filename: %d\n", stat(filename, &s));
					full_path = filename;
				} else {
					perror("file not exist");
					exit(1);
				}
			}

			if (execv(full_path, args) == -1) {
				perror("execv failed");
				exit(1);
			}

			exit(0);
		} else if (childPid < 0) {
			perror("Fork failed");
		} else {
			// parent process
			int returnStatus;

			signal(SIGINT, sigint);
			signal(SIGTSTP, sigtstp);

			// parent process wait for the child process to finish
			waitpid(childPid, &returnStatus, WUNTRACED);
			if (returnStatus != 0) {
				kill(childPid, SIGINT);
			}
			signal(SIGINT, SIG_DFL);
			signal(SIGTSTP, SIG_DFL);

			print_prompt();
		}
	}
	printf("\n");
}
