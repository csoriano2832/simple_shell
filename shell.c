#include "shell.h"

/**
 * main - runs a "simple" command line interpreter
 *
 * Return: Always 0 (Sucess)
 */
int main(void)
{
	char *line, **args;
	int flag, interactive = isatty(STDIN_FILENO);

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
			flag = spawn_process(args);
			if (flag == 1)
			{
				perror("execution fail");
				free(line);
				free(args);
				exit(EXIT_FAILURE);
			}
			free(args);
		}
		free(line);
	} while (interactive);
	return (0);
}

/**
 * get_input - reads user input and stores into a buffer
 *
 * Return: The line read from stdin as a string
 */
char *get_input(void)
{
	char *buffer = NULL;
	size_t bufsize = 1024;
	int bytesRead = 0;

	buffer = malloc(sizeof(char) * bufsize);

	bytesRead = read(STDIN_FILENO, buffer, bufsize);

	if (bytesRead == 0)
	{
		_putchar('\n');
		free(buffer);
		exit(EXIT_SUCCESS);
	}
	else if (bytesRead == -1)
	{
		perror("Error: could not read");
		exit(EXIT_FAILURE);
	}

	buffer[bytesRead - 1] = '\0';
	fflush(stdin);

	return (buffer);
}

/**
 * string_to_args - splits string from buffer into single worded arguments
 * @line: a command with optional arguments
 *
 * Return: An array of word separated tokens from line
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
 * @args: an array of single worded arguments
 *
 * Return: 0 if process executed succesfully, otherwise 1.
 */
int spawn_process(char *args[])
{
	pid_t forkedPid;
	int status = 0, wstatus;

	forkedPid = fork();
	if (forkedPid == -1)
	{
		perror("Error: forking");
	}

	if (forkedPid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			status = 1;
			return (status);
		}
	}
	else
	{
		wait(&wstatus);
	}

	return (status);
}
