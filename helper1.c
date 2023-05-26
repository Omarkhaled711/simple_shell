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
 * num_to_string - converts an integer to a string
 * @num: the integer to convert
 *
 * Return: a pointer to the string
 */
char *num_to_string(int num)
{
	int digit_count = 0, temp = num;
	char *result_str;

	if (num < 0)
	{
		digit_count++;
		temp = -num;
	}
	if (num == 0)
		digit_count = 1;
	else
	{
		while (temp != 0)
		{
			temp /= 10;
			digit_count++;
		}
	}
	result_str = malloc(sizeof(char) * (digit_count + 1));
	if (!result_str)
	{
		perror("malloc");
		return (NULL);
	}
	result_str[digit_count] = '\0';
	if (num < 0)
	{
		result_str[0] = '-';
		num = -num;
	}
	while (digit_count != 0)
	{
		digit_count--;
		result_str[digit_count] = '0' + num % 10;
		num /= 10;
	}
	return (result_str);
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
/**
 * remove_comments - Deletes comments from the input string
 *
 * @input_string: The input string
 *
 * Return: The input string without comments
 */
char *remove_comments(char *input_string)
{
	int i, comment_start;

	comment_start = 0;

	for (i = 0; input_string[i]; i++)
	{
		if (input_string[i] == '#')
		{
			if (i == 0)
			{
				free(input_string);
				return (NULL);
			}
			if (input_string[i - 1] == ' ' || input_string[i - 1] == ';' ||
				input_string[i - 1] == '\t')
				comment_start = i;
		}
	}

	if (comment_start != 0)
	{
		input_string = _realloc(input_string, i, comment_start + 1);
		input_string[comment_start] = '\0';
	}
	return (input_string);
}
/**
 * check_syntax_error - Checks if there is a syntax error in the input string
 *
 * @shell_info: Pointer to the shell data structure
 * @input_string: The input string to check
 *
 * Return: 0 if there is a syntax error, 1   otherwise
 */
int check_syntax_error(Shell_Info *shell_info, char *input_string)
{
	int begin_index = 0;
	int first_char_index = 0;
	int error_index = 0;

	first_char_index = get_first_character_index(input_string, &begin_index);
	if (first_char_index == -1)
	{
		print_syntax_error(shell_info, input_string, begin_index, 0);
		return (0);
	}
	error_index = get_error_operator_index(input_string + begin_index, 0,
					*(input_string + begin_index));
	if (error_index != 0)
	{
		print_syntax_error(shell_info, input_string, begin_index + error_index, 1);
		return (0);
	}
	return (1);
}
