#include "shell.h"

/**
 * create_directory_node - Create a directory node object
 *
 * @path: string
 * Return: Path_Dir*
 */
Path_Dir *create_directory_node(char *path)
{
	Path_Dir *node = malloc(sizeof(*node));

	if (node == NULL)
	{
		return (NULL);
	}
	node->path = _strdup(path);
	if (node->path == NULL)
	{
		free(node);
		return (NULL);
	}
	node->len = _strlen(path);
	node->next = NULL;
	return (node);
}

/**
 * append_directory_node - append node directory to path list
 *
 * @list: the list
 * @node: the directory node
 * Return: Path_Dir*
 */
Path_Dir *append_directory_node(Path_Dir *list, Path_Dir *node)
{
	Path_Dir *last;

	if (list == NULL)
	{
		return (node);
	}
	last = list;
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = node;
	return (list);
}

/**
 * get_path_directories - Get the path directories object
 *
 * Return: Path_Dir*
 */
Path_Dir *get_path_directories()
{
	char *path_variable = _getenv("PATH");
	Path_Dir *node, *directories;
	char *dir, *copy_path;

	if (path_variable == NULL || *path_variable == '\0')
	{
		return (NULL);
	}
	copy_path = _strdup(path_variable);
	if (copy_path == NULL)
	{
		return (NULL);
	}
	directories = NULL;
	dir = strtok(copy_path, ":");
	while (dir != NULL)
	{
		if (*dir != '\0')
		{
			node = create_directory_node(dir);
			if (node == NULL)
			{
				free_path_list(directories);
				free(copy_path);
				return (NULL);
			}
			directories = append_directory_node(directories, node);
		}
		dir = strtok(NULL, ":");
	}
	free(copy_path);
	return (directories);
}
/**
 * free_path_list - frees a linked list of directories in PATH
 * @head: pointer to the head of the linked list
 */
void free_path_list(Path_Dir *head)
{
	Path_Dir *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->path);
		free(temp);
	}
}
