#include "shell.h"

/**
 * get_first_character_index - Finds the index of the first
 * non-whitespace character
 *
 * @input_string: The input string
 * @first_char_index: Pointer to the index of the first
 * non-whitespace character
 *
 * Return: 0 on success, -1 if the first non-whitespace character is
 * a separator operator
 */
int get_first_character_index(char *input_string, int *first_char_index)
{
	for (*first_char_index = 0; input_string[*first_char_index];
			(*first_char_index)++)
	{
		if (input_string[*first_char_index] == ' '
			|| input_string[*first_char_index] == '\t')
			continue;

		if (input_string[*first_char_index] == ';'
			|| input_string[*first_char_index] == '|'
				|| input_string[*first_char_index] == '&')
			return (-1);

		break;
	}
	return (0);
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

/**
 * replace_variables - expanding commands if they cotain $
 *
 * @input: input command
 * @shell_info: info about shell
 * Return: char pointer (string)
 */
char *replace_variables(char *input, Shell_Info *shell_info)
{
	variable_list_t *head, *current;
	char *status_str, *modified_input;
	int original_len, new_len;

	head = NULL;
	status_str = num_to_string(shell_info->status);
	original_len = check_variables(&head, input, status_str, shell_info);

	if (head == NULL)
	{
		free(status_str);
		return (input);
	}
	current = head;
	new_len = 0;
	while (current != NULL)
	{
		new_len += (current->val_len - current->var_len);
		current = current->next;
	}
	new_len += original_len;
	modified_input = malloc(sizeof(char) * (new_len + 1));
	modified_input[new_len] = 0;
	replace_input(&head, input, modified_input, new_len);

	free(input);
	free(status_str);
	free_variable_list(&head);

	return (modified_input);
}

