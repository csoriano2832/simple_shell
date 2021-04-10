#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int _putchar(char c);
int _puts(char *str);
int _strlen(char *str);
int _strcmp(char *str1, char *str2);
char *get_input(void);
char **string_to_args(char *line);
void spawn_process(char *args[]);
char *_getenv(const char *name);

#endif
