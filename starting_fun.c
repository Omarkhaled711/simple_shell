#include "shell.h"

/**
 * start_interactive - starts the interactive shell
 *
 * @current: current shell info
 * @env: the env variables
 */
void start_interactive(Shell_Info *current, char *env[])
{
	char *command, **formatted;
	int check;

	current->counter = 0;
	while (1)
	{
		(current->counter)++;
		write(STDOUT_FILENO, "($) ", 4);
		command = read_command(current->PATH);
		if (command == NULL)
			continue;
		remove_comments(command);
		formatted = format_command(command, current->status);
		if (formatted == NULL)
		{
			free(command);
			continue;
		}
		check = check_builtin(formatted[0]);
		if (check >= 0)
			execute_builtin(check, command, formatted, current);
		else if (is_directory(formatted[0]))
		{
			print_error(current, formatted[0], NO_PERMISSION);
			current->status = NO_PERMISSION;
		}
		process_command(formatted, env, current);
		free(command);
		free_string_array(formatted);
	}
}

/**
 * start_non_interactive - starts shell
 *
 * @mode: to determine piped or from file
 * @current: shell info
 * @env: env variable
 * @argv: string arguments
 */
void start_non_interactive(int mode, Shell_Info *current, char *env[],
							char *argv[])
{
	char **commands = get_non_interactive_commands(mode, argv);
	char **formatted, *command;
	int check;

	current->counter = 0;
	while (commands[current->counter])
	{
		command = commands[current->counter];
		(current->counter)++;
		remove_comments(command);
		formatted = format_command(command, current->status);
		if (formatted == NULL)
		{
			free(command);
			continue;
		}
		check = check_builtin(formatted[0]);
		if (check >= 0)
			execute_builtin(check, command, formatted, current);
		else if (is_directory(formatted[0]))
		{
			print_error(current, formatted[0], NO_PERMISSION);
			current->status = NO_PERMISSION;
		}
		process_command(formatted, env, current);
		free(command);
		free_string_array(formatted);
	}
}
