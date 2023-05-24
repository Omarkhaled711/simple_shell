#include "shell.h"

/**
 * check_builtin - checks if a cmd is a builtin or not
 *
 * @cmd: the command
 * Return: int
 */
int check_builtin(char *cmd)
{
	if (_strcmp(cmd, "env") == 0)
		return (ENV_BUILTIN);
	if (_strcmp(cmd, "exit") == 0)
		return (EXIT_BUILTIN);
	return (-1);
}
/**
 * execute_builtin - executes builtin
 * @choose: get the right builtin
 * @command: the command
 * @formatted: the formatted command
 * @current: current shell info
 * Return: void
 */
void execute_builtin(int choose, char *command, char **formatted,
						Shell_Info *current)
{
	if (choose == ENV_BUILTIN)
	{
		print_env();
	}
	else if (choose == EXIT_BUILTIN)
	{
		execute_exit(command, formatted, current);
	}
}

/**
 * print_env - prints the environment variables
 * Return: void
 */
void print_env(void)
{
	int i;
	char newline = '\n';

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, &newline, 1);
	}
}

/**
 * free_all - a wrapper function for freeing funcs
 *
 * @command: the command
 * @formatted: the formatted command
 * @PATH: the list of directories of path
 * Return: void
 */
void free_all(char *command, char **formatted, Path_Dir *PATH)
{
	free(command);
	free_path_list(PATH);
	free_string_array(formatted);
}
/**
 * execute_exit - handles the exit command
 * @command: the command
 * @formatted: the formatted command
 * @current: current shell info
 * Return: void
 */
void execute_exit(char *command, char **formatted, Shell_Info *current)
{
	int n;

	if (formatted[1] == NULL)
	{
		free_all(command, formatted, current->PATH);
		exit(current->status);
	}

	if (_strlen(formatted[1]) > 9)
	{
		current->status = EXIT_WITH_ERROR;
		print_error(current, formatted[1], EXIT_WITH_ERROR);
		return;
	}

	n = _atoi(formatted[1]);
	if (n == -1)
	{
		current->status = EXIT_WITH_ERROR;
		print_error(current, formatted[1], EXIT_WITH_ERROR);
		return;
	}
	free_all(command, formatted, current->PATH);
	exit(n);
}
