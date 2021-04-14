#include "shell.h"

/**
 * main - runs a "simple" command line interpreter
 *
 * Return: Always 0 (Sucess)
 */
int main(void)
{
	char *line, **args, *path, **dirs, *fullPath;
	int idx = 0, flag = 0, pathFound, interactive = isatty(STDIN_FILENO);
	struct stat st;

	do {
		if (interactive == 1)
			_puts("$ ");

		line = get_input();

		if (_strcmp(line, "exit") == 0)
			interactive = 0;

		else if (_strcmp(line, "env") == 0)
		{
			for (idx = 0; environ[idx]; idx++)
			{
				_puts(environ[idx]);
				_putchar('\n');
			}
		}
		else
		{
			args = string_to_args(line);
			path = _getenv("PATH");
			dirs = _getpath(path);

			idx = 0;
			pathFound = 0;
			while (dirs[idx])
			{
				fullPath = _strcat(dirs[idx], args[0]);
				if (stat(fullPath, &st) == 0)
				{
					args[0] = fullPath;
					pathFound = 1;
					break;
				}
				else
				{
					free(fullPath);
					idx++;
				}
			}

			flag = spawn_process(args);
			if (flag == 1)
			{
				perror(args[0]);
				free(dirs);
				free(path);
				free(args);
				free(line);
				exit(EXIT_FAILURE);
			}
			if (pathFound == 1)
				free(fullPath);
			free(dirs);
			free(path);
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

	args = malloc(sizeof(char *) * 100);
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
