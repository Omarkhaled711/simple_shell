#include "shell.h"

/**
 * main - Entry point to the shell
 * @argc: arguements count
 * @argv: array of argument strings
 * @env: array of env strings
 * Return: 0
 */
int main(int argc, char *argv[], char *env[])
{
	Shell_Info current;
	int mode;
	Path_Dir *path;

	current.status = 0;
	current.name = argv[0];
	mode = get_mode(argc);
	path = get_path_directories();
	current.PATH = path;
	if (mode == INTERACTIVE_MODE)
	{
		start_interactive(&current, env);
	}
	else
	{
		start_non_interactive(mode, &current, env, argv);
	}
	free_path_list(current.PATH);
	exit(current.status);
}
