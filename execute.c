#include "shell.h"


/**
 * execute_command - executes command
 *
 * @shell: a struct object contains shell info
 * Return: int
 */
int execute_command(Shell_Info *shell)
{
	int (*builtin_function_ptr)(Shell_Info *shell);

	if (shell->args[0] == NULL)
	{
		return (1);
	}
	builtin_function_ptr = get_builtin(shell->args[0]);
	if (builtin_function_ptr != NULL)
	{
		return (builtin_function_ptr(shell));
	}
	return (execute_external_command(shell));
}
/**
 * get_builtin - Returns a function pointer to the appropriate builtin command.
 * @command: The command string.
 * Return: A function pointer to the appropriate builtin command.
*/
int (*get_builtin(char *command))(Shell_Info *)
{
	int (*builtin_function_ptr)(Shell_Info *);

	if (command == NULL)
		return (NULL);

	if (_strcmp(command, "env") == 0)
		builtin_function_ptr = print_env;
	else if (_strcmp(command, "exit") == 0)
		builtin_function_ptr = exit_shell;
	else
		builtin_function_ptr = NULL;

	return (builtin_function_ptr);
}
/**
 * check_executable - determines if is an executable
 *
 * @shell: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int check_executable(Shell_Info *shell)
{
	struct stat st;
	int i;
	char *input;

	input = shell->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	get_error(shell, 127);
	return (-1);
}

/**
 * execute_external_command - executeutes command lines input
 *
 * @shell: shell data
 * Return: 1 on success.
 */
int execute_external_command(Shell_Info *shell)
{
	pid_t pd, wpd;
	int state, execute;
	char *directory;
	(void) wpd;

	execute = check_executable(shell);
	if (execute == -1)
		return (1);
	if (execute == 0)
	{
		directory = find_command_path(shell->args[0], shell->env);
		if (check_error_access(directory, shell) == 1)
			return (1);
	}
	pd = fork();
	if (pd == 0)
	{
		if (execute == 0)
			directory = find_command_path(shell->args[0], shell->env);
		else
			directory = shell->args[0];
		execve(directory + execute, shell->args, shell->env);
	}
	else if (pd < 0)
	{
		perror(shell->argv[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	shell->status = state / 256;
	return (1);
}
