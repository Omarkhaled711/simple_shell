#include "shell.h"

/**
 * process_token - Processes a token and returns a command string.
 * @token: The token to process.
 * @status: The exit status of the previous command.
 * Return: A command string, or NULL on failure.
*/
char *process_token(char *token, int status)
{
	char *command;

	if (_strcmp("$?", token) == 0)
		command = get_status(status);
	else if (_strcmp("$$", token) == 0)
		command = get_process_id();
	else
		command = _strdup(token);
	return (command);
}
/**
 * free_argv - frees the memory allocated for the argv array and its contents
 * @av: pointer to the Argv struct
 */
void free_argv(Argv *av)
{
	unsigned int i;

	if (av == NULL)
	{
		return;
	}

	if (av->argv != NULL)
	{
		for (i = 0; i < av->argc; i++)
		{
			free(av->argv[i]);
		}
		free(av->argv);
	}

	av->argv = NULL;
	av->argc = 0;
}
/**
 * _realloc - similar to the realloc funtionin the stldib.h
 * @ptr: pointer to the existing memory
 * @old_size: old size
 * @new_size: new size
 * Return: a void pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i;
	void *p;
	char *access1, *access2;

	if (old_size == new_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{	free(ptr);
		return (NULL);
	}
	p = malloc(new_size);
	if (p == 0)
		return (NULL);
	access1 = p;
	access2 = ptr;
	if (old_size > new_size)
		old_size = new_size;
	for (i = 0; i < old_size && ptr != NULL; i++)
		access1[i] = access2[i];
	if (p != ptr)
		free(ptr);
	return (p);

}
/**
 * split_command - Splits a string into tokens and returns an array of
 *  pointers to each token.\
 * @command: The string to tokenize.
 * @status: The exit status of the previous command.
 * Return: An Argv struct containing the array of tokens and their count.
*/
Argv split_command(char *command, int status)
{
	Argv av = {0};
	char *command_cpy, *token, *cmd;

	command_cpy = _strdup(command);
	if (command_cpy == NULL)
		return (av); /* empty Argv */
	token = strtok(command_cpy, TOK_DELIM);
	while (token != NULL)
	{
		cmd = process_token(token, status);
		if (cmd == NULL)
		{
			free_argv(&av);
			free(command_cpy);
			return (av); /*empty Argv */
		}
		av.argv = _realloc(av.argv, (av.argc) * sizeof(char *),
							(av.argc + 1) * sizeof(char *));
		if (av.argv == NULL)
		{
			free_argv(&av);
			free(command_cpy);
			return (av); /* empty Argv */
		}
		av.argv[av.argc++] = cmd;
		token = strtok(NULL, TOK_DELIM);
	}
	av.argv = _realloc(av.argv, av.argc * sizeof(char *),
							(av.argc + 1) * sizeof(char *));
	if (av.argv == NULL)
	{
		free_argv(&av);
		free(command_cpy);
		return (av); /* empty Argv */
	}
	av.argv[av.argc] = NULL;
	free(command_cpy);
	return (av);
}
/**
 * format_command - Splits a string into tokens and returns an array of
 *  pointers to each token.
 * @command: The string to tokenize.
 * @status: The exit status of the previous command.
 * Return: An array of pointers to the tokens, or NULL on failure.
*/
char **format_command(char *command, int status)
{
	Argv av = split_command(command, status);
	char **argv;

	if (av.argv == NULL)
		return (NULL);

	argv = av.argv;

	av.argv = NULL; /*prevent argv from being freed */

	free_argv(&av);
	return (argv);
}
