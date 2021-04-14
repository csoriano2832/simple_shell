#include "shell.h"

/**
 * _getenv - searches for any existing environment variable
 * @name: name of the environment variable to search
 *
 * Return: the value of the string variable
 */
char *_getenv(const char *name)
{
	int idx, jdx;
	char *match;

	for (idx = 0; environ[idx] != NULL; idx++)
	{
		for (jdx = 0; environ[idx][jdx] != '\0'; jdx++)
		{
			if (environ[idx][jdx] != name[jdx])
			{
				break;
			}
			else if (environ[idx][jdx + 1] == '=')
			{
				if (name[jdx + 1] == '\0')
				{
					match = _strdup(&environ[idx][jdx + 2]);
					return (match);
				}

			}
		}
	}
	return (NULL);
}

/**
 * _getpath - tokenizes the path string into directories
 * @path: the entire path string
 *
 * Return: the path divided in single directories
 */
char **_getpath(char *path)
{
	char **dirs;
	int idx, size = 1;
	char delim[] = ":";

	for (idx = 0; path[idx] != '\0'; idx++)
	{
		if (path[idx] == ':')
			size++;
	}

	dirs = malloc(sizeof(char *) * (size + 1));
	if (dirs == NULL)
		exit(EXIT_FAILURE);

	dirs[0] = strtok(path, delim);

	for (idx = 0; dirs[idx] != NULL; idx++)
		dirs[idx + 1] = strtok(NULL, delim);

	return (dirs);

}

/**
 * _strcat - concatenates two string
 * @dest: where src will be appended
 * @src: string to be appended
 *
 * Return: dest after src has been appended
 */
char *_strcat(char *dest, char *src)
{
	int i, j, size = 0;
	char *newDir;

	size = _strlen(dest);
	size += _strlen(src);

	newDir = malloc(sizeof(char) * (size + 2));

	for (i = 0; dest[i] != '\0'; i++)
		newDir[i] = dest[i];

	newDir[i] = '/';
	i++;

	for (j = 0; src[j] != '\0'; j++)
	{
		newDir[i + j] = src[j];
	}

	newDir[i + j] = '\0';

	return (newDir);
}

/**
 * _freeall - frees all alocated memory
 * @line: user input
 * @args: input divided into tokens
 * @path: value of PATH variable in a single string
 * @dirs: path divided into directories
 *
 * Return: nothing
 */
void _freeall(char *line, char **args, char *path, char **dirs)
{
	free(dirs);
	free(path);
	free(args);
	free(line);
}
