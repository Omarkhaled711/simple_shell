#include "shell.h"

/**
 * get_mode - Get the mode of the shell
 *
 * @argc: num of args
 * Return: int
 */
int get_mode(int argc)
{
	struct stat stdin_stat;

	fstat(STDIN_FILENO, &stdin_stat);
	if (isatty(STDIN_FILENO) && argc == 1)
	{
		return (INTERACTIVE_MODE);
	}

	switch (argc)
	{
		case 1:
			return (NOT_INTERACTIVE_PIPED_MODE);
		default:
			return (NOT_INTERACTIVE_MODE);
	}

	return (INVALID_MODE_ERR);
}
/**
 * exit_shell - exits shell with a give value
 *
 * @PATH: the list of path directories
 * @x: the value to exit with
 */
void exit_shell(Path_Dir *PATH, int x)
{
	free(PATH);
	exit(x);
}
/**
 * read_command - reads command from user
 *
 * @PATH: the list of path directories
 * Return: char*
 */
char *read_command(Path_Dir *PATH)
{
	ssize_t read_line;
	size_t n = 0;
	char *temp_command = NULL, *command;

	read_line = getline(&temp_command, &n, stdin);
	if (read_line == EOF)
	{
		free(temp_command);
		exit_shell(PATH, 0);
	}
	if (temp_command[0] == '\n' && read_line == 1)
	{
		free(temp_command);
		return (NULL);
	}
	temp_command[read_line - 1] = 0;
	command = _strdup(temp_command);
	if (command == NULL)
	{
		free(temp_command);
		exit_shell(PATH, EXIT_FAILURE);
	}
	free(temp_command);
	return (command);
}

/**
 * remove_comments - remove comments from input string
 * @command: input string
 */
void remove_comments(char *command)
{
	unsigned int len = _strlen(command);
	unsigned int i = 0;

	int in_word = 0;

	for (i = 0; i < len; i++)
	{
		if (command[i] == ' ')
		{
			in_word = 0;
		}
		else if (command[i] == '#')
		{
			if (!in_word)
			{
				command[i] = '\0';
				break;
			}
		}
		else
		{
			in_word = 1;
		}
	}
}
/**
 * is_directory - checks if what's given is a directory or not
 * @file: argument
 * Return: 1 if the file is directory, 0 otherwise
 */
int is_directory(char *file)
{
	struct stat st;

	if (stat(file, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			return (1);
		}
	}
	return (0);
}
