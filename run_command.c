#include "shell.h"

/**
 * run_command - runs the command if possible
 *
 * @command: the command to run
 * @read_val: check the value returned by getline
 *
 * Return: void
 */

void run_command(char *command, int read_val)
{
	INFO_t cmd;
	int check;

	if (read_val == -1)
	{
		if (errno == 0) /* Ctrl + D has been pressed */
			exit_shell(0);
		else
			/* failed to reserver memory, will see what to print */
			/* print_error(VERY_LONG_COMMAND);  //a macro to be defined */
	}
	break_command(&cmd);
	check = check_if_valid(&cmd);
	if (check <= 0)
		print_error(check);
	else
		run_execve(&cmd);
}
