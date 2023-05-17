#include "shell.h"

/**
 * exit_shell - exit shell (custom implementation of the exit builtin)
 *
 * @value: the value to exit with
 * Return: void
 */
void exit_shell(int value)
{
	exit(value); /* temp implementation */
}
