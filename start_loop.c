#include "shell.h"
/**
 * initialize_shell_info - Initialize the shell_info data structure
 *
 * @shell_info: Pointer to the shell_info data structure
 * @argv: Argument vector
 *
 * Return: No return value
 */
void initialize_shell_info(Shell_Info *shell_info, char **argv)
{
	unsigned int i = 0;
	char **envp = environ;

	shell_info->argv = argv;
	shell_info->input = NULL;
	shell_info->args = NULL;
	shell_info->status = 0;
	shell_info->counter = 1;

	while (envp[i] != NULL)
		i++;

	shell_info->env = malloc(sizeof(char *) * (i + 1));

	i = 0;
	while (envp[i] != NULL)
	{
		shell_info->env[i] = _strdup(envp[i]);
		i++;
	}

	shell_info->env[i] = NULL;
	shell_info->pid = num_to_string(getpid());
}

/**
 * start_loop - Starts the shell loop
 * @shell_info: Pointer to the Shell_Info structure
 *
 * Return: No return value
 */
void start_loop(Shell_Info *shell_info)
{
	int should_loop = 1, is_eof;
	char *input_line = NULL;
	size_t bufsize = 0;

	while (should_loop)
	{
		input_line = NULL;
		write(STDIN_FILENO, "($) ", 4);
		is_eof = getline(&input_line, &bufsize, stdin);
		if (is_eof != -1)
		{
			input_line = remove_comments(input_line);
			if (input_line == NULL)
				continue;

			if (check_syntax_error(shell_info, input_line) == 0)
			{
				shell_info->status = 2;
				free(input_line);
				continue;
			}

			input_line = replace_variables(input_line, shell_info);
			should_loop = split_commands(shell_info, input_line);
			shell_info->counter += 1;
			free(input_line);
		}
		else
		{
			should_loop = 0;
			free(input_line);
		}
	}
}

