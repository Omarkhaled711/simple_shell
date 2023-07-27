#include "shell.h"

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

/**
 * print_syntax_error - Prints a syntax error message
 *
 * @shell_info: Pointer to the shell data structure
 * @input: The input string that caused the syntax error
 * @error_index: The index of the error in the input string
 * @is_operator_error: A flag indicating whether the syntax error is
 * related to an operator
 *
 * Return: No return value
 */
void print_syntax_error(Shell_Info *shell_info, char *input, int error_index,
						int is_operator_error)
{
char *operator_str, *prefix, *suffix, *error_msg, *counter_str;
int error_msg_len;

if (is_operator_error)
	operator_str = (input[error_index + 1] == ';' ? ";;" : ";");
else if (input[error_index] == '|')
	operator_str = (input[error_index + 1] == '|' ? "||" : "|");
else if (input[error_index] == '&')
	operator_str = (input[error_index + 1] == '&' ? "&&" : "&");
else
	operator_str = "";
prefix = ": Syntax error: \"";
suffix = "\" unexpected\n";
counter_str = num_to_string(shell_info->counter);
error_msg_len = _strlen(shell_info->argv[0]) + _strlen(counter_str) +
				_strlen(operator_str) + _strlen(prefix) + _strlen(suffix) + 2;

error_msg = malloc(error_msg_len + 1);
if (error_msg != NULL)
{
	_strcpy(error_msg, shell_info->argv[0]);
	_strcat(error_msg, ": ");
	_strcat(error_msg, counter_str);
	_strcat(error_msg, prefix);
	_strcat(error_msg, operator_str);
	_strcat(error_msg, suffix);

	write(STDERR_FILENO, error_msg, error_msg_len);

	free(error_msg);
}
free(counter_str);
}

/**
 * get_error_operator_index - Get the error operator index object
 *
 * @input_string: input str
 * @i: int
 * @last: int
 * Return: int
 */
int get_error_operator_index(char *input_string, int i, char last)
{
	int count;

	count = 0;
	if (*input_string == '\0')
		return (0);
	switch (*input_string)
	{
		case ' ':
		case '\t':
			return (get_error_operator_index(input_string + 1, i + 1, last));
		case ';':
			if (last == '|' || last == '&' || last == ';')
				return (i);
			break;
		case '|':
			if (last == ';' || last == '&')
				return (i);
			if (last == '|')
			{
				count = repeated_char(input_string);
				if (count == 0 || count > 1)
					return (i);
			}
			break;
		case '&':
			if (last == ';' || last == '|')
				return (i);
			if (last == '&')
			{
				count = repeated_char(input_string);
				if (count == 0 || count > 1)
					return (i);
			}
			break;
		default:
			break;
	}
	return (get_error_operator_index(input_string + 1, i + 1, *input_string));
}
