#include "shell.h"

/**
 * main - runs a "simple" command line interpreter
 *
 *
 */
int main(int argc, char *argv[])
{
	char *string = NULL;
	char **args = NULL;
	int interactive = 0;
	(void) argc;
	(void) argv;

	do {
	
		if ((interactive = isatty(STDIN_FILENO)) == 1)
			_puts("($) ");

		string = get_input();

		args = string_to_args(string);

		spawn_process(args);

		free(string);
		free(args);
	
	} while (interactive);
	
	return (0);
}

/**
 * get_input - reads user input and stores into a buffer
 *
 *
 */
char *get_input()
{
	char *buffer = NULL;
	size_t bufsize = 0;

	if (getline(&buffer, &bufsize, stdin) == -1)
		perror("prompt");

	return (buffer);
}

/**
 * string_to_args - splits string from buffer into single worded arguments
 *
 *
 */
char **string_to_args(char *string)
{
	char **args;
	int index;
	char delim[] = "\n ";

	args = (char **) malloc(100 * sizeof(char *));

	args[0] = strtok(string, delim);

	for (index = 0; args[index] != NULL; index++)
	{
		args[index + 1] = strtok(NULL, delim);
	}

	return (args);
}

/**
 * spawn_process - creates a child process and executes a command
 *
 *
 */
void spawn_process(char *args[])
{
	pid_t forkedPid;
	int status;

	forkedPid = fork();
	if (forkedPid == -1) 
		perror("spawn_process");

	if (forkedPid == 0)
	{
		if (execve(args[0], args, NULL) == -1) 
			perror("spawn_process");
	}
	else
	{
		wait(&status);
	}
}
