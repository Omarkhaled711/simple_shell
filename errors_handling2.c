#include "shell.h"
/**
 * error_get_cd - generates an error message for the cd command
 * in the get_cd function
 * @shell: data structure containing relevant data
 *
 * Return: the error message
 */
char *error_get_cd(Shell_Info *shell)
{
	int total_length, id_length;
	char *error_msg, *counter_str, *error_type;

	counter_str = num_to_string(shell->counter);

	if (shell->args[1][0] == '_')
	{
		error_type = ": Illegal option ";
		id_length = 2;
	}
	else
	{
		error_type = ": can't change directory to ";
		id_length = _strlen(shell->args[1]);
	}

	total_length = _strlen(shell->argv[0]) + _strlen(shell->args[0]);
	total_length += _strlen(counter_str) + _strlen(error_type) + id_length + 5;
	error_msg = malloc(sizeof(char) * (total_length + 1));

	if (error_msg == NULL)
	{
		free(counter_str);
		return (NULL);
	}

	error_msg = concat_cd(shell, error_type, error_msg, counter_str);
	free(counter_str);
	return (error_msg);
}
/**
  * concat_cd - resposible for concatenation of
  * error messages
  * @shell: shell info
  * @error: output message
  * @msg: printed message
  * @counter: counter lines
  *
  * Return: error msg
  */
char *concat_cd(Shell_Info *shell, char *msg, char *error, char *counter)
{
	char *illegal;

	illegal = malloc(3);
	_strcpy(error, shell->argv[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, ": ");
	_strcat(error, shell->args[0]);
	_strcat(error, msg);

	if (shell->args[1][0] == '_')
	{
		illegal[0] = '-';
		illegal[1] = shell->args[1][1];
		illegal[2] = 0;
		_strcat(error, illegal);
	}
	else
	{
		_strcat(error, shell->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	free(illegal);
	return (error);
}
/**
 * check_error_access - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @shell: data structure
 *
 * Return: 1 if there is an error, 0 if not
 */
int check_error_access(char *dir, Shell_Info *shell)
{
	int end_value = 0;

	switch (!dir)
	{
		case 1:
			get_error(shell, COMMAND_NOT_FOUND_ERROR);
			end_value = 1;
			break;
		default:
			switch (_strcmp(shell->args[0], dir))
			{
				case 0:
					if (access(shell->args[0], X_OK) == -1)
					{
						get_error(shell, PERMISSION_ERROR);
						end_value = 1;
					}
					break;
				default:
					if (access(dir, X_OK) == -1)
					{
						get_error(shell, PERMISSION_ERROR);
						end_value = 1;
					}
					free(dir);
					break;
			}
			break;
	}

	return (end_value);
}
