#ifndef SHELL_H
#define SHELL_H

#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "stdio.h"
#include "stdlib.h"
#include <errno.h>

/**
 * struct CMD_INFO - new struct type
 * @command: string
 * @path: string
 * @options: string
 * @rest: string
 */
typedef struct CMD_INFO
{
	char *command;
	char *path;
	char *options;
	char *rest;
} INFO_t;

size_t _getline(char **string, size_t *n, FILE *stream);
void start_loop(void);
void run_command(char *command, int read_val);
void break_command(INFO_t *cmd);
int check_if_valid(INFO_t *cmd);
void exit_shell(int value);
void handle_error(INFO_t *cmd);
void run_exceve(INFO_t *cmd);

#endif
