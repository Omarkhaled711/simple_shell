#include "shell.h"

/**
 * split_commands - Splits command lines according to the separators.
 * @shell_info: A pointer to the Shell_Info struct.
 * @input: The input string to be split and executed.
 * Return: 0 if exit command, 1 otherwise.
*/
int split_commands(Shell_Info *shell_info, char *input)
{
	separator_list_node_t *sep_head = NULL, *sep_node;
	commands_list_node_t *command_head = NULL, *command_node;
	int should_loop = 1;

	add_sep_nodes(&sep_head, input);
	add_command_nodes(&command_head, input);
	sep_node = sep_head;
	command_node = command_head;
	while (command_node != NULL)
	{
		shell_info->input = command_node->command_line;
		shell_info->args = tokenize_input(shell_info->input);
		should_loop = execute_command(shell_info);
		free(shell_info->args);
		if (should_loop == 0)
		{
			break;
		}

		go_to_next_command(&sep_node, &command_node, shell_info);

		if (command_node != NULL)
		{
			command_node = command_node->next;
		}
	}
	free_separation_list(&sep_head);
	free_commands_list(&command_head);
	return (should_loop);
}
/**
 * tokenize_input - Tokenizes the input string into an array of strings.
 * @input: The input string to be tokenized.
 * Return: An array of strings containing the tokens.
 */
char **tokenize_input(char *input)
{
	size_t buffer_size = TOKEN_BUFFER_SIZE;
	size_t i = 0;
	char *token, **tokens = malloc(sizeof(char *) * buffer_size);

	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = strtok(input, TOKEN_DELIMITERS);
	tokens[i] = token;

	while (token != NULL)
	{
		i++;
		if (i == buffer_size)
		{
			buffer_size += TOKEN_BUFFER_SIZE;
			tokens = realloc_double_pointer(tokens, i, sizeof(char *) * buffer_size);

			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOKEN_DELIMITERS);
		tokens[i] = token;
	}
	return (tokens);
}
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

	/*
	*if (_strcmp(command, "cd") == 0)
	*	builtin_function_ptr = cd_command;
	*/
	if (_strcmp(command, "env") == 0)
		builtin_function_ptr = print_env;
	else if (_strcmp(command, "exit") == 0)
		builtin_function_ptr = exit_shell;
	/*
	*else if (_strcmp(command, "help") == 0)
	*	builtin_function_ptr = get_help;
	*else if (_strcmp(command, "setenv") == 0)
	*	builtin_function_ptr = setenv_command;
	*else if (_strcmp(command, "unsetenv") == 0)
	*	builtin_function_ptr = unsetenv_command;
	*/
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
