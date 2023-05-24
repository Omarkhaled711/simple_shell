#include "shell.h"

/**
 * num_to_string - converts an integer to a string
 * @num: the integer to convert
 *
 * Return: a pointer to the string
 */
char *num_to_string(int num)
{
	int digit_count = 0, temp = num;
	char *result_str;

	if (num == 0)
		digit_count = 1;
	else
	{
		while (temp != 0)
		{
			temp /= 10;
			digit_count++;
		}
	}
	result_str = malloc(sizeof(char) * (digit_count + 1));
	if (!result_str)
	{
		perror("malloc");
		return (NULL);
	}
	result_str[digit_count] = '\0';
	while (digit_count != 0)
	{
		digit_count--;
		result_str[digit_count] = '0' + num % 10;
		num /= 10;
	}
	return (result_str);
}
/**
 * get_process_id - As the name suggests
 *
 * Return: a string
 */
char *get_process_id()
{
	char *ppid_get;
	pid_t pid = getpid();

	ppid_get = num_to_string(pid);
	return (ppid_get);
}
/**
 * get_status - as the name suggest.
 * @status: the status to convert to string.
 * Return: string.
 */
char *get_status(int status)
{
	char *status_string;

	status_string = num_to_string(status);
	return (status_string);

}
/**
 * process_command - processing
 *
 * @formatted: formatted command
 * @env: env var
 * @current: shell info
 */
void process_command(char **formatted, char *env[], Shell_Info *current)
{
	char *find_path = NULL;

	current->status = 0;
	if (access(formatted[0], X_OK) == 0)
	{
		run_command(formatted[0], formatted, env, current->status);
		return;
	}
	find_path = check_PATH(formatted[0], current->PATH);
	if (find_path != NULL)
	{
		run_command(find_path, formatted, env, current->status);
		free(find_path);
		return;
	}
	print_error(current, formatted[0], NOT_FOUND);
	current->status = NOT_FOUND;
}
/**
 * check_PATH - checks if the command has a valid path in the path env
 * @command: the command to search for
 * @PATH: the list of paths to search in
 * Return: a pointer containing the complete path to the command or NULL.
 */
char *check_PATH(char *command, Path_Dir *PATH)
{
	char *complete_path = NULL;
	int exist = 0;
	unsigned int len;

	if (PATH == NULL)
		return (NULL);

	for (; PATH != NULL; PATH = PATH->next)
	{
		len = _strlen(PATH->path) + _strlen(command) + 2;
		if (len > MAX_PATH_LENGTH)
		{
			write(STDERR_FILENO, "ERROR: Path too long\n", 21);
			continue;
		}

		complete_path = (char *)malloc(len * sizeof(char));
		if (complete_path == NULL)
			return (NULL);
		_strcpy(complete_path, PATH->path);
		_strcat(complete_path, "/");
		_strcat(complete_path, command);
		if (access(complete_path, X_OK) == 0)
		{
			exist = 1;
			break;
		}
		else
			free(complete_path);
	}
	if (exist)
		return (complete_path);
	else
		return (NULL);
}
