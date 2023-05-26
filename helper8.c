#include "shell.h"
/**
 * error_get_cd - generates an error message for the cd command
 * in the get_cd function
 * @shell: data structure containing relevant data
 *
 * Return: the error message
 */
char *error_get_cd(Shell_Info *shell)
{
	int total_length, id_length;
	char *error_msg, *counter_str, *error_type;

	counter_str = num_to_string(shell->counter);

	if (shell->args[1][0] == '_')
	{
		error_type = ": Illegal option ";
		id_length = 2;
	}
	else
	{
		error_type = ": can't change directory to ";
		id_length = _strlen(shell->args[1]);
	}

	total_length = _strlen(shell->argv[0]) + _strlen(shell->args[0]);
	total_length += _strlen(counter_str) + _strlen(error_type) + id_length + 5;
	error_msg = malloc(sizeof(char) * (total_length + 1));

	if (error_msg == NULL)
	{
		free(counter_str);
		return (NULL);
	}

	error_msg = concat_cd(shell, error_type, error_msg, counter_str);
	free(counter_str);
	return (error_msg);
}
/**
  * concat_cd - resposible for concatenation of
  * error messages
  * @shell: shell info
  * @error: output message
  * @msg: printed message
  * @counter: counter lines
  *
  * Return: error msg
  */
char *concat_cd(Shell_Info *shell, char *msg, char *error, char *counter)
{
	char *illegal;

	illegal = malloc(3);
	_strcpy(error, shell->argv[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, ": ");
	_strcat(error, shell->args[0]);
	_strcat(error, msg);

	if (shell->args[1][0] == '_')
	{
		illegal[0] = '-';
		illegal[1] = shell->args[1][1];
		illegal[2] = 0;
		_strcat(error, illegal);
	}
	else
	{
		_strcat(error, shell->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	free(illegal);
	return (error);
}
/**
 * add_sep_nodes - adds a node to the separator list
 *
 * @head_s: head of separator
 * @input: the command input
 */
void add_sep_nodes(separator_list_node_t **head_s, char *input)
{
	int i;

	convert_special_chars(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_separator_node(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_separator_node(head_s, input[i]);
			i++;
		}
	}
}
/**
 * add_command_nodes - adds a node to the command list
 *
 * @head_c: head of commands
 * @input: the command input
 */
void add_command_nodes(commands_list_node_t **head_c, char *input)
{
	char *line;

	line = strtok(input, ";|&");
	do {
		convert_special_chars(line, 1);
		add_command_node(head_c, line);
		line = strtok(NULL, ";|&");
	} while (line != NULL);
}
/**
 * convert_special_chars - converts | and & to non-printed chars and vice-versa
 *
 * @input: input string
 * @bool: type of converting
 *
 * Return: None
 */
void convert_special_chars(char *input, int bool)
{
	int i, non_printable1 = 5, non_printable2 = 6;

	for (i = 0; input[i]; i++)
	{
		if (bool == 0)
		{
			if (input[i] == '|' && input[i + 1] != '|')
				input[i] = non_printable1;
			else if (input[i] == '&' && input[i + 1] != '&')
				input[i] = non_printable2;
		}
		else
		{
			input[i] = (input[i] == non_printable1 ? '|' : input[i]);
			input[i] = (input[i] == non_printable2 ? '&' : input[i]);
		}
	}
}
