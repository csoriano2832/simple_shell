#include "shell.h"
void _sighandler(int sig_num);

/**
 * main - runs a "simple" command line interpreter
 *
 * Return: Always 0 (Sucess)
 */
int main(void)
{
	char *line, **args, *path, **dirs, *fullPath;
	int idx, flag = 0, pathFound, interactive = isatty(STDIN_FILENO);
	struct stat st;

	do {
		if (interactive == 1)
			_puts("$ ");
		
		line = get_input();
		if (line == NULL)
			continue;

		if (_checkbuiltins(line))
			continue;

		args = string_to_args(line);
		path = _getenv("PATH");
		dirs = _getpath(path);

		idx = 0, pathFound = 0;
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
			_freeall(line, args, path, dirs);
			exit(127);
		}
		if (pathFound == 1)
			free(fullPath);
		_freeall(line, args, path, dirs);
	} while (1);
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
	size_t bufsize = 0;
	int bytesRead = 0, idx = 0;

	bytesRead = getline(&buffer, &bufsize, stdin);
	
	if (bytesRead == EOF)
	{
		if (isatty(STDIN_FILENO) == 1)
			_putchar('\n');
		free(buffer);
		exit(EXIT_SUCCESS);
	}

	if (bytesRead == 1)
	{
		free(buffer);
		return (NULL);
	}
	
	buffer[bytesRead - 1] = '\0';

	while (buffer[idx] == ' ' || buffer[idx] == '\t')
	{
		if (buffer[idx + 1] == '\0')
		{
			free(buffer);
			return(NULL);
		}
		idx++;
	}
	
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
 * Return: 0 if process executed succesfully, otherwise, 1.
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
		EXIT_CODE = WEXITSTATUS(wstatus);
	}
	return (status);
}

/**
 * _checkbuiltins - checks if user input equals one of the shell keywords
 * @line: the user input
 *
 * Return: 1 if input matched one of the builtins, otherwise, 0
 */
int _checkbuiltins(char *line)
{
	int idx;

	if (_strcmp(line, "exit") == 0)
	{
		free(line);
		exit(EXIT_CODE);
	}

	else if (_strcmp(line, "env") == 0)
	{
		for (idx = 0; environ[idx]; idx++)
		{
			_puts(environ[idx]);
			_putchar('\n');
		}
		free(line);
		return (1);
	}
	else
	{
		return (0);
	}
}
