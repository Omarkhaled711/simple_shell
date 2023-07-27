#include "shell.h"


/**
 * free_variable_list - Deallocates memory for a linked list of variables.
 * @head: A pointer to the head of the linked list.
 * Return: void
*/
void free_variable_list(variable_list_t **head)
{
	variable_list_t *curr;

	if (head == NULL || *head == NULL)
	{
		return;
	}
	curr = *head;
	while (curr != NULL)
	{
		variable_list_t *temp = curr;

		curr = curr->next;
		free(temp);
	}
	*head = NULL;
}

/**
 * free_separation_list - frees a separator_list_node_t
 * @head: the header of the linked list.
 * Return: no return.
 */
void free_separation_list(separator_list_node_t **head)
{
	separator_list_node_t *temp, *current;

	if (head != NULL)
	{
		current = *head;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*head = NULL;
	}
}
/**
 * free_commands_list- frees a commands_list_node_t
 * @head: head of the linked list.
 * Return: no return.
 */
void free_commands_list(commands_list_node_t **head)
{
	commands_list_node_t *temp, *current;

	if (head != NULL)
	{
		current = *head;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*head = NULL;
	}
}
