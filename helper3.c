#include "shell.h"

/**
 * replace_input - expands the input if it contains a var
 *
 * @head: head to var list
 * @input: the input command
 * @modified_input: the new input
 * @new_len: the new len
 * Return: void
 */
void replace_input(variable_list_t **head, char *input, char *modified_input,
					int new_len)
{
	variable_list_t *current;
	int i, j;

	current = *head;
	for (i = 0, j = 0; i < new_len; i++, j++)
	{
		if (input[j] == '$')
		{
			if (current && current->var_len > 0 && current->val_len > 0)
			{
				modified_input = copy_variable_value(current, modified_input, &i);
				j += current->var_len;
				current = current->next;
			}
			else
			{
				modified_input[i] = input[j];
			}
		}
		else
		{
			modified_input[i] = input[j];
		}
	}
}

char *copy_variable_value(variable_list_t *variable, char *modified_input,
						int *index)
{
	int i, j;

	for (i = 0, j = *index; i < variable->val_len; i++, j++)
	{
		modified_input[j] = variable->value[i];
	}

	*index = j - 1;

	return (modified_input);
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
 * add_variable_node - adds a variable to the end of a variable_list_t list.
 *
 * @head: pointer to the head of the linked list.
 * @var_length: length of the variable name.
 * @value: pointer to the value of the variable.
 * @value_length: length of the value of the variable.
 *
 * Return: pointer to the head of the linked list.
 */
variable_list_t *add_variable_node(variable_list_t **head, int var_length,
					char *value, int value_length)
{
	variable_list_t *new_node, *temp_node;

	new_node = malloc(sizeof(variable_list_t));
	if (new_node == NULL)
	{
		perror("malloc error");
		return (NULL);
	}

	new_node->var_len = var_length;
	new_node->value = value;
	new_node->val_len = value_length;
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		temp_node = *head;
		while (temp_node->next != NULL)
		{
			temp_node = temp_node->next;
		}
		temp_node->next = new_node;
	}

	return (*head);
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
