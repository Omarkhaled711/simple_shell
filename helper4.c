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
	return (commands);
}

/**
 * get_from_piped - get input through pipes .
 * Return: splitted commands
 */
char **get_from_piped()
{
	char input_buffer[INPUT_BUFFER_SIZE], *text, **lines;
	ssize_t bytesRead;
	size_t totalchar = 0;

	while ((bytesRead = read(STDIN_FILENO, input_buffer, INPUT_BUFFER_SIZE)) > 0)
	{
		totalchar += bytesRead;
	}
	if (bytesRead == -1)
	{
		perror("read");
		exit(-1);
	}
	if (totalchar > INPUT_BUFFER_SIZE)
		input_buffer[INPUT_BUFFER_SIZE - 1] = '\0';
	else
		input_buffer[totalchar - 1] = '\0';

	text = malloc(sizeof(char) * (totalchar));
	if (!text)
		return (NULL);
	text = _strdup(input_buffer);
	if (text)
		lines = text_to_commands(text);
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
/**
 * print_file_open_problem - file isn't possible to open
 *
 * @program_name: the program name
 * @file_name: the file name
 * Return: void
 */
void print_file_open_problem(char *program_name, char *file_name)
{
	print_error_header(program_name, 0);
	write(STDERR_FILENO, "Can't open ", 11);
	write(STDERR_FILENO, file_name, _strlen(file_name));
	write(STDERR_FILENO, "\n", 1);
}
