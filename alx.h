#ifndef _ALX_H_
#define _ALX_H_
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>

extern char **environ;

char *show_input(void);
char *_strcat(char *src);
int _strlen(char *str);
void place(char *str);
char *findfile(char *command);
char *find_command(char *command);
int compare(char *s1, char *s2);
int _strcmpdir(char *s1, char *s2);
int charput(char c);
void place(char *str);
char *str_concat(char *s1, char *s2);
int lookforslash(char *cmd);
int compareExit(char *s1, char *s2);
int compareEnv(char *s1, char *s2);
void run_command(char **cmd);
char **identify_string(char *parameter);
void controlC(int sig);
void CLI(void);
#endif
