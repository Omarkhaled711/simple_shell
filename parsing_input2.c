#include "shell.h"

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

/**
 * check_variables - check if the typed variable is $$ or $?
 *
 * @var_list: pointer to the head of the variable linked list
 * @input: input string to check for variables
 * @status: last status of the shell to use for $? variable
 * @data: pointer to Shell_Info struct containing shell data
 * Return: length of the input string
 */
int check_variables(variable_list_t **var_list, char *input, char *status,
					Shell_Info *data)
{
	int i = 0;
	int status_len = _strlen(status);
	int pid_len = _strlen(data->pid);

	while (input[i])
	{
		if (input[i] == '$')
		{
			switch (input[i + 1])
			{
			case '?':
				add_variable_node(var_list, 2, status, status_len);
				i++;
				break;
			case '$':
				add_variable_node(var_list, 2, data->pid, pid_len);
				i++;
				break;
			case '\n':
			case '\0':
			case ' ':
			case '\t':
			case ';':
				add_variable_node(var_list, 0, NULL, 0);
				break;
			default:
				check_environment_variable(var_list, input + i, data);
				break;
			}
		}
		i++;
	}

	return (i);
}


/**
 * check_environment_variable - checks if the input string is an
 *  environment variable
 *  @var_list: pointer to the head of the variable linked list
 * @input: input string to check for environment variables
 * @data: pointer to Shell_Info struct containing shell data
 * Return: None
*/
void check_environment_variable(variable_list_t **var_list, char *input,
								Shell_Info *data)
{
	int row, chr, j, value_length;
	char **env_list = data->env;

	for (row = 0; env_list[row]; row++)
	{
		for (j = 1, chr = 0; env_list[row][chr]; chr++)
		{
			if (env_list[row][chr] == '=')
			{
				value_length = _strlen(env_list[row] + chr + 1);
				add_variable_node(var_list, j, env_list[row] + chr + 1, value_length);
				return;
			}

			if (input[j] == env_list[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; input[j]; j++)
	{
		if (input[j] == ' ' || input[j] == '\t' || input[j] == ';'
				|| input[j] == '\n')
			break;
	}
	add_variable_node(var_list, j, NULL, 0);
}
