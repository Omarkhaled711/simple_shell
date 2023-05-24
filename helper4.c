#include "shell.h"

/**
 * get_non_interactive_commands - As the name suggests
 *
 * @mode: file or piped
 * @argv: to get the program and file names
 * Return: char**
 */
char **get_non_interactive_commands(int mode, char *argv[])
{
	char **commands;

	if (mode == NOT_INTERACTIVE_PIPED_MODE)
	{
		commands = get_from_piped();
	}
	else if (mode == NOT_INTERACTIVE_MODE)
	{
		commands = get_from_file(argv[0], argv[1]);
	}
	if (!commands)
		exit(0);
	return (commands);
}

/**
 * my_isspace - check for spaces and empty strings
 *
 * @c: the char to check
 * Return: int
 */
int my_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
			 || c == '\f' || c == '\v');
}
/**
 * get_from_piped - get input through pipes .
 * Return: splitted commands
 */
char **get_from_piped()
{
	char buffer[2048], *input = NULL, **lines = NULL;
	ssize_t bytes_read;
	size_t total_chars = 0;
	int i, has_input = 0;

	while ((bytes_read = read(STDIN_FILENO, buffer, 2048)) > 0)
		total_chars += bytes_read;
	if (bytes_read == -1)
	{
		perror("read");
		exit(-1);
	}
	if (total_chars > 2048)
		buffer[2047] = '\0';
	else
		buffer[total_chars - 1] = '\0';
	for (i = 0; buffer[i]; i++)
	{
		if (!my_isspace(buffer[i]))
		{
			has_input = 1;
			break;
		}
	}
	if (!has_input)
		return (NULL);
	total_chars = _strlen(buffer);
	input = (char *)malloc((total_chars + 1) * sizeof(char));
	if (input != NULL)
	{
		_strcpy(input, buffer);
		input[total_chars] = '\0';
		lines = text_to_commands(input);
	}
	return (lines);
}

/**
 * get_from_file -  Gets data from file object
 *
 * @file_name: the file name
 * @program_name: the program name
 * Return: char**
 */
char **get_from_file(char *file_name, char *program_name)
{
	struct stat fileStat;
	char *text, **commands;
	int file_descriptor;

	if (stat(file_name, &fileStat) == -1)
	{
		print_file_open_problem(program_name, file_name);
		exit(NOT_FOUND);
	}
	if (!S_ISREG(fileStat.st_mode))
		exit(0);
	file_descriptor = open(file_name, O_RDONLY);
	if (file_descriptor == -1)
	{
		perror("read");
		exit(-1);
	}
	text = read_file(file_descriptor, fileStat.st_size);
	if (!text)
	{
		perror("read");
		exit(-1);
	}
	close(file_descriptor);
	commands = _strsplit(text, "\n");
	return (commands);
}

/**
 * read_file - read data from file
 *
 * @file_descriptor: the descriptor of the file
 * @file_size: the size of the file
 * Return: char*
 */
char *read_file(int file_descriptor, size_t file_size)
{
	char *buffer = malloc(file_size + 1);
	int bytes_read;

	if (!buffer)
		exit(-1);
	bytes_read = read(file_descriptor, buffer, file_size);

	if (bytes_read == -1)
	{
		perror("read");
		exit(-1);
	}
	buffer[bytes_read] = '\0';
	return (buffer);
}
