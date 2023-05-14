#include "shell.h"

/**
 * main - Entry point to the program
 *
 * @argc: the number of args
 * @argv: the array string of args
 * @envp: the arry of environment strings
 * Return: 0
 */
int main(int argc, char *argv, char *envp[])
{
	if (argc == 1)
	{
		start_loop();
	}
	else
	{
		/*run one command or print an error*/
	}

	return (0);
}

