#include "shell.h"

/**
 * go_next - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @shell: data structure
 *
 * Return: none
 */
void go_to_next_command(separator_list_node_t **list_s,
						commands_list_node_t **list_l, Shell_Info *shell)
{
	int loop_sep = 1;
	separator_list_node_t *ls_s = *list_s;
	commands_list_node_t *ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (shell->status == 0)
			switch (ls_s->separator_char)
			{
				case '&':
				case ';':
					loop_sep = 0;
					break;
				case '|':
					ls_l = ls_l->next;
					ls_s = ls_s->next;
					break;
			}
		else
			switch (ls_s->separator_char)
			{
				case '|':
				case ';':
					loop_sep = 0;
					break;
				case '&':
					ls_l = ls_l->next;
					ls_s = ls_s->next;
					break;
			}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
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
/**
 * execute_external_command - executeutes command lines input
 *
 * @shell: shell data
 * Return: 1 on success.
 */
int execute_external_command(Shell_Info *shell)
{
	pid_t pd, wpd;
	int state, execute;
	char *directory;
	(void) wpd;

	execute = check_executable(shell);
	if (execute == -1)
		return (1);
	if (execute == 0)
	{
		directory = find_command_path(shell->args[0], shell->env);
		if (check_error_access(directory, shell) == 1)
			return (1);
	}
	pd = fork();
	if (pd == 0)
	{
		if (execute == 0)
			directory = find_command_path(shell->args[0], shell->env);
		else
			directory = shell->args[0];
		execve(directory + execute, shell->args, shell->env);
	}
	else if (pd < 0)
	{
		perror(shell->argv[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	shell->status = state / 256;
	return (1);
}
/**
 * _realloc - similar to the realloc funtionin the stldib.h
 * @ptr: pointer to the existing memory
 * @old_size: old size
 * @new_size: new size
 * Return: a void pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i;
	void *p;
	char *access1, *access2;

	if (old_size == new_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	p = malloc(new_size);
	if (p == 0)
		return (NULL);
	access1 = p;
	access2 = ptr;
	if (old_size > new_size)
		old_size = new_size;
	for (i = 0; i < old_size && ptr != NULL; i++)
		access1[i] = access2[i];
	if (p != ptr)
		free(ptr);
	return (p);
}
