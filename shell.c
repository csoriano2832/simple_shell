#include "shell.h"

/**
 * main - runs a "simple" command line interpreter
 *
 *
 */
int main(void)
{
	char *line;
	char **args;
	int interactive = isatty(STDIN_FILENO);

	do {

		if (interactive == 1)
			_puts("($) ");

		line = get_input();

		if (_strcmp(line, "exit") == 0)
		{
			interactive = 0;
		}
		else if (_strcmp(line, "env") == 0)
		{
			int index;

			for (index = 0; environ[index]; index++)
			{
				_puts(environ[index]);
				_putchar('\n');
			}
		}
		else
		{
			args = string_to_args(line);

			spawn_process(args);

			free(args);
		}
		free(line);

	} while (interactive);

	return (0);
}

/**
 * get_input - reads user input and stores into a buffer
 *
 *
 */
char *get_input(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	int bytesRead = 0;

	bytesRead = getline(&buffer, &bufsize, stdin);
	if (bytesRead == -1)
	{
		perror("Error: getting input");
		exit(EXIT_FAILURE);
	}
	buffer[bytesRead - 1] = '\0';
	fflush(stdin);

	return (buffer);
}

/**
 * string_to_args - splits string from buffer into single worded arguments
 *
 *
 */
char **string_to_args(char *line)
{
	char **args;
	int index;
	char delim[] = "\n ";

	args = malloc(100 * sizeof(char *));
	if (args == NULL)
		exit(EXIT_FAILURE);

	args[0] = strtok(line, delim);

	for (index = 0; args[index] != NULL; index++)
	{
		args[index + 1] = strtok(NULL, delim);
	}

	args[index + 1] = NULL;

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
	int wstatus;

	forkedPid = fork();
	if (forkedPid == -1)
	{
		perror("Error: forking");
	}

	if (forkedPid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("Error: executing command");
			free(args);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&wstatus);
	}
}
