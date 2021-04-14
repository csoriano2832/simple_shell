#ifndef SHELL_H
#define SHELL_H

/* LIBRARIES */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;
int __attribute((unused)) EXIT_CODE;

/* PROTOTYPES */
int _putchar(char c);
int _puts(char *str);
int _strlen(char *str);
int _strcmp(char *str1, char *str2);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
char *get_input(void);
char **string_to_args(char *line);
int spawn_process(char *args[]);
char *_getenv(const char *name);
char **_getpath(char *path);
int _checkbuiltins(char *line);
void _freeall(char *line, char **args, char *path, char **dirs);
void _sighandler(int sig_num);

#endif
