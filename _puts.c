#include "shell.h"

/**
 * _puts - writes a string of characters to stdout
 *
 */
int _puts(char *str)
{
	return (write(STDOUT_FILENO, str, _strlen(str)));
}

/**
 * _putchar - writes a single character to stdout
 *
 */
int _putchar(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

/**
 * _strlen - gets the length of a string
 *
 */
int _strlen(char *str)
{

	int bytes;

	for (bytes = 0; str[bytes] != '\0'; bytes++);

	return (bytes);
}



