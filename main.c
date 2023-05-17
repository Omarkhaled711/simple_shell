#include "shell.h"

/**
 * main - the main function for the shell
 *
 * @argc: the number of arguments
 * @argv: the list of arguments
 * Return: 0 (success), 1 (fail)
 */

int main(int argc, char **argv)
{
	/* small template to be modified */
	char *str;

	if (argc != 1)
	{
		/* error message */
	}
	while (true)
	{
		printf("$ ");
		if (getline(str, 100, stdin) == -1)
		{
			/* exit the loop and terminate */
		}
		if (execve(str, str, NULL) < 0)
		{
			/* some changes should be made */
			perror("Error");
		}
	}
	return (0);
}
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
}
