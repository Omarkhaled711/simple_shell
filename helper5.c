#include "shell.h"

/**
 * run_command - executes the command.
 * @path: the path of the program
 * @command: the command provided to the shell
 * @env: as the name suggests
 * @status: as the name suggests
 * Return: void
 */

void run_command(char *path, char **command, char **env, int *status)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execve(path, command, env);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, status, WUNTRACED);
		*status  = WEXITSTATUS(*status);
	}
}

/**
 * _getenv - retrieves the value of the environment variable 'name'
 * @name: the name of the environment variable to retrieve
 *
 * Return: a pointer to the value of the environment variable, or NULL if the
 * variable is not found
 */
char *_getenv(const char *name)
{
	int i, j;

	if (name == NULL)
		return (NULL);

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '=' && name[j] != '\0'; j++)
		{
			if (environ[i][j] != name[j])
				break;
		}

		if (environ[i][j] == '=' && name[j] == '\0')
		{
			return (&environ[i][j + 1]);
		}
	}

	return (NULL);
}
/**
 * print_error_header - prints error header
 *
 * @name: name
 * @counter: the line at which the error occured
 */
void print_error_header(char *name, int counter)
{
	char *counter_string = num_to_string(counter);

	write(STDERR_FILENO, name, _strlen(name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, counter_string, _strlen(counter_string));
	write(STDERR_FILENO, ": ", 2);

	free(counter_string);
}

/**
 * print_error - prints error
 *
 * @current: Shell_Info object
 * @command: the command at which the error occurd
 * @error_type: the type of error
 */
void print_error(Shell_Info *current, char *command, int error_type)
{
	print_error_header(current->name, current->counter);

	if (error_type == 2)
		write(STDERR_FILENO, "exit", 4);
	else
		write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": ", 2);
	if (error_type == NOT_FOUND)
		write(STDERR_FILENO, "not found\n", 10);
	else if (error_type == NO_PERMISSION)
		write(STDERR_FILENO, "Permission denied\n", 18);
	else if (error_type == 2)
	{
		write(STDERR_FILENO, "Illegal number: ", 16);
		write(STDERR_FILENO, command, _strlen(command));
		write(STDERR_FILENO, "\n", 1);
	}
}
