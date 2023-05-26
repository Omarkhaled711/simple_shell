#include "shell.h"

/**
 * print_env - Prints the environment variables.
 * @shell: A pointer to the Shell_Info struct.
 * Return: 1 on success, 0 on failure.
 */
int print_env(Shell_Info *shell)
{
	unsigned int i, j;

	if (shell == NULL || shell->env == NULL)
	{
		return (0);
	}

	for (i = 0; shell->env[i] != NULL; i++)
	{
		j = 0;
		while (shell->env[i][j] != '\0')
		{
			j++;
		}
		write(STDOUT_FILENO, shell->env[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}

	shell->status = 0;
	return (1);
}
/**
 * exit_shell - Exits the shell with the specified status code.
 * @shell: A pointer to the Shell_Info struct.
 * Return: 0 on success, 1 on failure.
*/
int exit_shell(Shell_Info *shell)
{
	if (shell == NULL || shell->args == NULL)
	{
		return (1);
	}

	if (shell->args[1] != NULL)
	{
		unsigned int max_status, sh_status;
		int is_digit, str_len;

		max_status = (unsigned int)INT_MAX;
		sh_status = _atoi(shell->args[1]);
		is_digit = _isdigit(shell->args[1]);
		str_len = _strlen(shell->args[1]);

		if (!is_digit || str_len > 10 || sh_status > max_status)
		{
			get_error(shell, 2);
			shell->status = 2;
			return (1);
		}
		if (sh_status > max_status)
		{
			shell->status = sh_status % 256;
		}
		else
		{
			shell->status = (int)sh_status % 256;
		}
	}

	return (0);
}
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
 * cd_command - Changes the current directory.
 *
 * @shell - A pointer to the Shell_Info struct.
 * Return: 1 on success, 0 on failure.
 * int cd_command(Shell_Info *shell)
 * {
 * char *dir = shell->args[1];
 * if (dir == NULL || _strcmp("$HOME", dir) == 0 || _strcmp("~", dir) == 0
 *			|| _strcmp("--", dir) == 0)
 * {
 * return cd_home(shell);
 * }
 * if (_strcmp("-", dir) == 0)
 * {
 * return cd_pre(shell);
 * }
 * if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
 * {
 * return cd_dot(shell);
 * }
 * return cd_to(shell);
 * }
*/

