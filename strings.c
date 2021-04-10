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

/**
 * _strcmp - compares characters in two strings
 * @str1: first string
 * @str2: second string
 *
 * Return: Negative number if str2 is greater than str1
 * Positive number if str2 is lesser than str1
 * 0 if str1 and str2 are the same
 */
int _strcmp(char *str1, char *str2)
{
	int idx;

	for (idx = 0; str1[idx] == str2[idx]; idx++)
	{
		if (str1[idx] == '\0')
			return (0);
	}
	
	return (str1[idx] - str2[idx]);
}
