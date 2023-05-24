#include "shell.h"

/**
 * text_to_commands - convert piped texts to commands
 * @text: the piped text
 * Return: splitted commands
 */
char **text_to_commands(char *text)
{
	char *token, *cmd, *copy_txt;
	char **lines;
	int i = 0;
	unsigned int c_count;

	copy_txt = _strdup(text);
	if (copy_txt == NULL)
		return (NULL);
	c_count = count_char_pip_mode(copy_txt, '\n');
	lines = malloc(c_count * sizeof(char *));
	token = strtok(copy_txt, "\n");
	cmd = _strdup(token);
	lines[i++] = cmd;
	while (token != NULL)
	{
		token = strtok(NULL, "\n");
		if (token != NULL)
		{
			cmd = _strdup(token);
			lines[i++] = cmd;
		}
	}
	free(text);
	return (lines);
}

/**
 * count_char_pip_mode - helper function
 *
 * @str: the text
 * @c: character
 * Return: count
 */
unsigned int count_char_pip_mode(char *str, char c)
{
	unsigned int count = 0;

	while (*str != '\0')
	{
		if (*str != c)
			count++;
		str++;
	}
	return (count + 1);
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

