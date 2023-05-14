#include "shell.h"

/* implementing helper functions*/
/**
 * get_path - gets path
 * @path: pointer to a string
 * @command: string
 * Return: void
 */
void get_path(char **path, char *command)
{
	/*temp implementation*/
	*path = command;
}

/**
 * get_options - gets path
 * @options: pointer to a string
 * @command: string
 * Return: void
 */
void get_options(char **options, char *command)
{
	/*temp implementation*/
	*option = NULL;
}

/**
 * get_rest - gets rest
 * @rest: pointer to a string
 * @command: string
 * Return: void
 */
void get_rest(char **rest, char *command)
{
	/*temp implementaion*/
	*rest = NULL
}

/*Implementing the function to be called*/
/**
 * break_command - breaks a command to parts
 * @cmd: a struct variable
 * Return: void
 */

void break_command(INFO_t *cmd)
{
	get_path(&(cmd->path), cmd->command);
	get_options(&(cmd->options), cmd->command);
	get_rest(&(cmd->rest), cmd->command);
}

