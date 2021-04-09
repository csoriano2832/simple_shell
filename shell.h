#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int _putchar(char c);
int _puts(char *str);
int _strlen(char *str);
void print_prompt();
char *get_input();
void spawn_process(char *args[]);
char **string_to_args(char *string);
void free_args(char **args);

#endif
