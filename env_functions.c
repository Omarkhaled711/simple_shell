#include "shell.h"

/**
 * compare_env - compares the env var names
 * with the name passed.
 * @env_name: name of the environment variable
 * @name: the name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int compare_env(const char *env_name, const char *name)
{
	int i;

	for (i = 0; env_name[i] != '='; i++)
	{
		if (env_name[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}
/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if found, or NULL if not found.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr;
	int i, mov;

	ptr = NULL;
	mov = 0;
	for (i = 0; _environ[i]; i++)
	{
		mov = compare_env(_environ[i], name);
		if (mov)
		{
			ptr = _environ[i];
			break;
		}
	}

	return (ptr + mov);
}

/**
 * find_command_path - finds the location of a command.
 *  @command_name: name of the command to be located.
 *  @envp: environment variables.
 *  Return: Pointer to the location of the command, or NULL if not found.
*/
char *find_command_path(char *command_name, char **envp)
{
	char *path_variable_value, *path_copy, *directory_token, *command_path;
	int directory_length, command_length;
	struct stat file_stat;
	int path_index = 0;

	if (command_name[0] == '/')
		return (stat(command_name, &file_stat) == 0 ? command_name : NULL);
	path_variable_value = _getenv("PATH", envp);
	if (!path_variable_value)
		return (NULL);
	path_copy = _strdup(path_variable_value);
	directory_token = strtok(path_copy, ":");
	while (directory_token)
	{
		directory_length = _strlen(directory_token);
		command_length = _strlen(command_name);
		command_path = malloc(directory_length + command_length + 2);
		if (!command_path)
		{
			free(path_copy);
			return (NULL);
		}
		_strcpy(command_path, directory_token);
		_strcat(command_path, "/");
		_strcat(command_path, command_name);

		if (stat(command_path, &file_stat) == 0)
		{
			free(path_copy);
			return (command_path);
		}
		free(command_path);
		directory_token = strtok(NULL, ":");
	}
	free(path_copy);
	if (is_current_dir(command_name, &path_index) &&
			 stat(command_name, &file_stat) == 0)
		return (command_name);
	return (NULL);
}

/**
 * is_current_dir - checks if the current directory is in
 * the PATH environment variable.
 * @path: colon-separated list of directories in the PATH environment variable.
 * @i: pointer to the current index.
 *
 * Return: 1 if the current directory is in the PATH, 0 otherwise.
 */
int is_current_dir(char *path, int *i)
{
	int result = 0;

	switch (path[*i])
	{
		case ':':
			result = 1;
			break;

		default:
			while (path[*i] != ':' && path[*i] != '\0')
			{
				(*i)++;
			}

			if (path[*i] == ':')
			{
				(*i)++;
			}
			break;
	}

	return (result);
}
