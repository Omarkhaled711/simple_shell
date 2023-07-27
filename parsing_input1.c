#include "shell.h"


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

/**
 * copy_variable_value - copies the value of the current variable into the
 * modified_input string starting at the current index
 * @variable: pointer to a list
 * @modified_input: the modified input string
 * @index: the index
 * Return: modified_input
*/
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
