#include "shell.h"

/**
  * get_signal - take care of the  crtl + c call
  *
  * @sig: handle signal
  */
void get_signal(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n($) ", 5);
}
/**
 * free_memory - frees memory
 *
 * @shell: data structure
 * Return: no return
 */
void free_memory(Shell_Info *shell)
{
	unsigned int i;

	for (i = 0; shell->env[i]; i++)
	{
		free(shell->env[i]);
	}

	free(shell->env);
	free(shell->pid);
}
/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	Shell_Info shell;
	(void) ac;

	signal(SIGINT, get_signal);
	initialize_shell_info(&shell, av);
	start_loop(&shell);
	free_memory(&shell);
	shell.status = shell.status < 0 ? 255 : shell.status;
	return (shell.status);
}
