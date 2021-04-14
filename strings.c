#include "shell.h"

/**
 * _puts - writes a string of characters to stdout
 * @str: string to print
 *
 * Return: numbers of characters printed
 */
int _puts(char *str)
{
	return (write(STDOUT_FILENO, str, _strlen(str)));
}

/**
 * _putchar - writes a single character to stdout
 * @c: character to print
 *
 * Return: 1 if character was printed
 */
int _putchar(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

/**
 * _strlen - gets the length of a string
 * @str: the string to be evaluated
 *
 * Return: the length of the string
 */
int _strlen(char *str)
{

	int bytes;

	for (bytes = 0; str[bytes] != '\0'; bytes++)
		;

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

/**
 * _strdup - returns a duplicate of a given string
 * @str: a string
 *
 * Return: a pointer to the duplicate string
 */
char *_strdup(char *str)
{
	int idx, len = 0;
	char *dup;

	if (str == NULL)
		return (NULL);

	for (idx = 0; str[idx] != '\0'; idx++)
	{
		len++;
	}

	dup = malloc((sizeof(char) * len) + 1);
	if (dup == NULL)
		return (NULL);

	for (idx = 0; idx <= len; idx++)
	{
		dup[idx] = str[idx];
	}

	return (dup);
}
