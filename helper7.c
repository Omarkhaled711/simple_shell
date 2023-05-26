#include "shell.h"

/**
 * get_error - calls the error based on the type of error
 * @shell: data structure that contains arguments
 * @error_type: type of error
 * Return: error value
 */
int get_error(Shell_Info *shell, int error_type)
{
	char *error_msg = NULL;

	if (error_type == ENV_ERROR)
		error_msg = error_env(shell);
	else if (error_type == PERMISSION_ERROR)
		error_msg = error_path(shell);
	else if (error_type == COMMAND_NOT_FOUND_ERROR)
		error_msg = error_not_found(shell);
	else if (error_type == BUILTIN_ERROR)
	{
		if (_strcmp("exit", shell->args[0]) == 0)
			error_msg = error_exit(shell);
		else if (_strcmp("cd", shell->args[0]) == 0)
			error_msg = error_get_cd(shell);
	}
	if (error_msg != NULL)
	{
		write(STDERR_FILENO, error_msg, _strlen(error_msg));
		free(error_msg);
	}
	shell->status = error_type;
	return (error_type);
}
/**
 * error_env - generates an error message for environment errors
 * @shell: data structure that contains relevant data
 *
 * Return: the error message
 */
char *error_env(Shell_Info *shell)
{
	int total_length;
	char *error_msg;
	char *counter_str;
	char *command_name = shell->argv[0];
	char *error_suffix = ": Unable to add/remove from environment\n";

	counter_str = num_to_string(shell->counter);
	total_length = _strlen(shell->argv[0]) + _strlen(counter_str);
	total_length += _strlen(shell->args[0]) + _strlen(error_suffix) + 4;
	error_msg = malloc(sizeof(char) * (total_length + 1));

	if (error_msg == NULL)
	{
		free(error_msg);
		free(counter_str);
		return (NULL);
	}

	_strcpy(error_msg, command_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, counter_str);
	_strcat(error_msg, ": ");
	_strcat(error_msg, shell->args[0]);
	_strcat(error_msg, error_suffix);
	_strcat(error_msg, "\0");
	free(counter_str);

	return (error_msg);
}
/**
 * error_path - generates an error message for permission errors
 * @shell: data structure that contains relevant data
 *
 * Return: the error message
 */
char *error_path(Shell_Info *shell)
{
	int total_length;
	char *error_msg;
	char *counter_str;
	char *command_name = shell->argv[0];
	char *error_suffix = ": Permission denied\n";

	counter_str = num_to_string(shell->counter);
	total_length = _strlen(shell->argv[0]) + _strlen(counter_str) +
					_strlen(shell->args[0]) + 24;
	error_msg = malloc(sizeof(char) * (total_length + 1));

	if (error_msg == NULL)
	{
		free(error_msg);
		free(counter_str);
		return (NULL);
	}

	_strcpy(error_msg, command_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, counter_str);
	_strcat(error_msg, ": ");
	_strcat(error_msg, shell->args[0]);
	_strcat(error_msg, error_suffix);
	_strcat(error_msg, "\0");
	free(counter_str);

	return (error_msg);
}
/**
 * error_not_found - generates an error message for command not found errors
 * @shell: data structure that contains relevant data
 *
 * Return: the error message
 */
char *error_not_found(Shell_Info *shell)
{
	int total_length;
	char *error_msg;
	char *counter_str;
	char *command_name = shell->argv[0];
	char *error_suffix = ": not found\n";

	counter_str = num_to_string(shell->counter);
	total_length = _strlen(command_name) + _strlen(counter_str);
	total_length += _strlen(shell->args[0]) + 16;
	error_msg = malloc(sizeof(char) * (total_length + 1));

	if (error_msg == NULL)
	{
		free(error_msg);
		free(counter_str);
		return (NULL);
	}
	_strcpy(error_msg, command_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, counter_str);
	_strcat(error_msg, ": ");
	_strcat(error_msg, shell->args[0]);
	_strcat(error_msg, error_suffix);
	_strcat(error_msg, "\0");
	free(counter_str);
	return (error_msg);
}
/**
 * error_exit - generates an error message for shell exit errors
 * @shell: a structure containing shell data
 *
 * Return: the error message
 */
char *error_exit(Shell_Info *shell)
{
	char *command_name = shell->argv[0];
	char *illegal_num_msg = "Illegal number: ";
	char *counter_str = num_to_string(shell->counter);
	int total_length = _strlen(shell->argv[0]) + _strlen(counter_str);
	char *error_msg;

	total_length += _strlen(shell->args[0]) + _strlen(shell->args[1]) + 23;
	error_msg = malloc(sizeof(char) * (total_length + 1));
	if (error_msg == NULL)
	{
		free(counter_str);
		return (NULL);
	}

	_strcpy(error_msg, command_name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, counter_str);
	_strcat(error_msg, ": ");
	_strcat(error_msg, shell->args[0]);
	_strcat(error_msg, illegal_num_msg);
	_strcat(error_msg, shell->args[1]);
	_strcat(error_msg, "\n\0");
	free(counter_str);
	return (error_msg);
}
