#include "shell.h"

/**
 * get_first_character_index - Finds the index of the first
 * non-whitespace character
 *
 * @input_string: The input string
 * @first_char_index: Pointer to the index of the first
 * non-whitespace character
 *
 * Return: 0 on success, -1 if the first non-whitespace character is
 * a separator operator
 */
int get_first_character_index(char *input_string, int *first_char_index)
{
	for (*first_char_index = 0; input_string[*first_char_index];
			(*first_char_index)++)
	{
		if (input_string[*first_char_index] == ' '
			|| input_string[*first_char_index] == '\t')
			continue;

		if (input_string[*first_char_index] == ';'
			|| input_string[*first_char_index] == '|'
				|| input_string[*first_char_index] == '&')
			return (-1);

		break;
	}
	return (0);
}

/**
 * remove_comments - Deletes comments from the input string
 *
 * @input_string: The input string
 *
 * Return: The input string without comments
 */
char *remove_comments(char *input_string)
{
	int i, comment_start;

	comment_start = 0;

	for (i = 0; input_string[i]; i++)
	{
		if (input_string[i] == '#')
		{
			if (i == 0)
			{
				free(input_string);
				return (NULL);
			}
			if (input_string[i - 1] == ' ' || input_string[i - 1] == ';' ||
				input_string[i - 1] == '\t')
				comment_start = i;
		}
	}

	if (comment_start != 0)
	{
		input_string = _realloc(input_string, i, comment_start + 1);
		input_string[comment_start] = '\0';
	}
	return (input_string);
}
/**
 * split_commands - Splits command lines according to the separators.
 * @shell_info: A pointer to the Shell_Info struct.
 * @input: The input string to be split and executed.
 * Return: 0 if exit command, 1 otherwise.
*/
int split_commands(Shell_Info *shell_info, char *input)
{
	separator_list_node_t *sep_head = NULL, *sep_node;
	commands_list_node_t *command_head = NULL, *command_node;
	int should_loop = 1;

	add_sep_nodes(&sep_head, input);
	add_command_nodes(&command_head, input);
	sep_node = sep_head;
	command_node = command_head;
	while (command_node != NULL)
	{
		shell_info->input = command_node->command_line;
		shell_info->args = tokenize_input(shell_info->input);
		should_loop = execute_command(shell_info);
		free(shell_info->args);
		if (should_loop == 0)
		{
			break;
		}

		go_to_next_command(&sep_node, &command_node, shell_info);

		if (command_node != NULL)
		{
			command_node = command_node->next;
		}
	}
	free_separation_list(&sep_head);
	free_commands_list(&command_head);
	return (should_loop);
}
/**
 * tokenize_input - Tokenizes the input string into an array of strings.
 * @input: The input string to be tokenized.
 * Return: An array of strings containing the tokens.
 */
char **tokenize_input(char *input)
{
	size_t buffer_size = TOKEN_BUFFER_SIZE;
	size_t i = 0;
	char *token, **tokens = malloc(sizeof(char *) * buffer_size);

	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = strtok(input, TOKEN_DELIMITERS);
	tokens[i] = token;

	while (token != NULL)
	{
		i++;
		if (i == buffer_size)
		{
			buffer_size += TOKEN_BUFFER_SIZE;
			tokens = realloc_double_pointer(tokens, i, sizeof(char *) * buffer_size);

			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOKEN_DELIMITERS);
		tokens[i] = token;
	}
	return (tokens);
}

/**
 * go_next - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @shell: data structure
 *
 * Return: none
 */
void go_to_next_command(separator_list_node_t **list_s,
						commands_list_node_t **list_l, Shell_Info *shell)
{
	int loop_sep = 1;
	separator_list_node_t *ls_s = *list_s;
	commands_list_node_t *ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (shell->status == 0)
			switch (ls_s->separator_char)
			{
				case '&':
				case ';':
					loop_sep = 0;
					break;
				case '|':
					ls_l = ls_l->next;
					ls_s = ls_s->next;
					break;
			}
		else
			switch (ls_s->separator_char)
			{
				case '|':
				case ';':
					loop_sep = 0;
					break;
				case '&':
					ls_l = ls_l->next;
					ls_s = ls_s->next;
					break;
			}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}
