#include "shell.h"

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
 * find_command_path - finds the location of a command.
 *  @command_name: name of the command to be located.
 *  @envp: environment variables.
 *  Return: Pointer to the location of the command, or NULL if not found.
*/
char *find_command_path(char *command_name, char **envp)
{
	char *path_variable_value, *path_copy, *directory_token, *command_path;
	int directory_length, command_length;
	struct stat file_stat;
	int path_index = 0;

	if (command_name[0] == '/')
		return (stat(command_name, &file_stat) == 0 ? command_name : NULL);
	path_variable_value = _getenv("PATH", envp);
	if (!path_variable_value)
		return (NULL);
	path_copy = _strdup(path_variable_value);
	directory_token = strtok(path_copy, ":");
	while (directory_token)
	{
		directory_length = _strlen(directory_token);
		command_length = _strlen(command_name);
		command_path = malloc(directory_length + command_length + 2);
		if (!command_path)
		{
			free(path_copy);
			return (NULL);
		}
		_strcpy(command_path, directory_token);
		_strcat(command_path, "/");
		_strcat(command_path, command_name);

		if (stat(command_path, &file_stat) == 0)
		{
			free(path_copy);
			return (command_path);
		}
		free(command_path);
		directory_token = strtok(NULL, ":");
	}
	free(path_copy);
	if (is_current_dir(command_name, &path_index) &&
			 stat(command_name, &file_stat) == 0)
		return (command_name);
	return (NULL);
}

/**
 * is_current_dir - checks if the current directory is in
 * the PATH environment variable.
 * @path: colon-separated list of directories in the PATH environment variable.
 * @i: pointer to the current index.
 *
 * Return: 1 if the current directory is in the PATH, 0 otherwise.
 */
int is_current_dir(char *path, int *i)
{
	int result = 0;

	switch (path[*i])
	{
		case ':':
			result = 1;
			break;

		default:
			while (path[*i] != ':' && path[*i] != '\0')
			{
				(*i)++;
			}

			if (path[*i] == ':')
			{
				(*i)++;
			}
			break;
	}

	return (result);
}
/**
 * check_error_access - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @shell: data structure
 *
 * Return: 1 if there is an error, 0 if not
 */
int check_error_access(char *dir, Shell_Info *shell)
{
	int end_value = 0;

	switch (!dir)
	{
		case 1:
			get_error(shell, COMMAND_NOT_FOUND_ERROR);
			end_value = 1;
			break;
		default:
			switch (_strcmp(shell->args[0], dir))
			{
				case 0:
					if (access(shell->args[0], X_OK) == -1)
					{
						get_error(shell, PERMISSION_ERROR);
						end_value = 1;
					}
					break;
				default:
					if (access(dir, X_OK) == -1)
					{
						get_error(shell, PERMISSION_ERROR);
						end_value = 1;
					}
					free(dir);
					break;
			}
			break;
	}

	return (end_value);
}
