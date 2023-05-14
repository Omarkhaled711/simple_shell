#include "shell"

/**
 * start_loop - starts the infinit loop
 *
 * Return: void
 */

void start_loop(void)
{
	while (1)
	{
		char *command = NULL;
		size_t size = 30; /* it will be dynamically reallocated anyways */
		int read;

		read = _getline(&command, &size, stdin);
		run_command(command, read);
	}
}
