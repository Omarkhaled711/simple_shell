#include "shell.h"


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
 * add_command_node - adds a command line node to the end of a linked list.
 * @list_head: pointer to the head of the linked list.
 * @command_line: command line string to be added to the list.
 *
 * Return: Pointer to the head of the modified list.
 */
commands_list_node_t *add_command_node(commands_list_node_t **list_head,
									   char *command_line)
{
	commands_list_node_t *new_node, *current_node;

	new_node = malloc(sizeof(*new_node));
	if (new_node == NULL)
		return (NULL);

	new_node->command_line = command_line;
	new_node->next = NULL;

	if (*list_head == NULL)
	{
		/* List is empty, add the new node as the head */
		*list_head = new_node;
	}
	else
	{
		/* Traverse the list to find the last node */
		current_node = *list_head;
		while (current_node->next != NULL)
			current_node = current_node->next;

		/* Add the new node to the end of the list */
		current_node->next = new_node;
	}

	return (*list_head);
}
/**
 * add_separator_node - adds a separator node to the end of a list.
 * @list_head: pointer to the head of the list.
 * @separator: separator character to be added to the list.
 *
 * Return: Pointer to the head of the modified list.
 */
separator_list_node_t *add_separator_node(separator_list_node_t **list_head,
										  char separator)
{
	separator_list_node_t *new_node, *current_node;

	new_node = malloc(sizeof(*new_node));
	if (new_node == NULL)
		return (NULL);

	new_node->separator_char = separator;
	new_node->next = NULL;

	if (*list_head == NULL)
	{
		/* List is empty, add the new node as the head */
		*list_head = new_node;
	}
	else
	{
		/* Traverse the list to find the last node */
		current_node = *list_head;
		while (current_node->next != NULL)
			current_node = current_node->next;

		/* Add the new node to the end of the list */
		current_node->next = new_node;
	}
	return (*list_head);
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
