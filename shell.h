#ifndef SHELL_H
#define SHELL_H

/* INCLUDES*/
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>

extern char **environ;

#define TOKEN_BUFFER_SIZE 128
#define TOKEN_DELIMITERS " \t\r\n\a"
#define ENV_ERROR  -1
#define PERMISSION_ERROR  126
#define COMMAND_NOT_FOUND_ERROR  127
#define BUILTIN_ERROR  2

/**
 * struct info - struct that contains all relevant info on runtime
 * @argv: array of string of arguments
 * @args: tokens for the cmd
 * @input: the input by the user
 * @status: last status of the shell
 * @counter: a counter of lines
 * @env: environment variable
 * @pid: process ID of the shell
 */
typedef struct info
{
	char **argv;
	char **args;
	char *input;
	int status;
	int counter;
	char **env;
	char *pid;
} Shell_Info;

/**
 * struct variable_list - single linked list
 * @value: value of the variable
 * @val_len: length of the value
 * @var_len: length of the variable name
 * @next: pointer to the next node
 * Description: single linked list to store variables
 */
typedef struct variable_list
{
	char *value;
	int val_len;
	int var_len;
	struct variable_list *next;
} variable_list_t;

/**
 * struct separator_list_node - A node in a single-linked
 * list that stores separators.
 * @separator_char: The separator character.
 * @next: A pointer to the next node in the list.
*/
typedef struct separator_list_node
{
char separator_char;
struct separator_list_node *next;
} separator_list_node_t;

/**
 * struct command_line_list_node - A single-linked list node
 *  for storing command lines.
 * @command_line: The command line string.
 * @next: A pointer to the next node in the list.
 * @description A single-linked list to store command lines.
*/
typedef struct command_line_list_node
{
char *command_line;
struct command_line_list_node *next;
} commands_list_node_t;

void initialize_shell_info(Shell_Info *shell_info, char **argv);
char *num_to_string(int num);
void start_loop(Shell_Info *shell_info);
char *remove_comments(char *input_string);
int check_syntax_error(Shell_Info *shell_info, char *input_string);
int get_first_character_index(char *input_string, int *first_char_index);
void print_syntax_error(Shell_Info *shell_info, char *input, int error_index,
						int is_semicolon);
int get_error_operator_index(char *input_string, int i, char last);
char *replace_variables(char *input, Shell_Info *shell_info);
void replace_input(variable_list_t **head, char *input, char *new_input,
					int new_len);
char *copy_variable_value(variable_list_t *variable, char *new_input,
							int *index);
int check_variables(variable_list_t **var_list, char *input, char *status,
					Shell_Info *data);
variable_list_t *add_variable_node(variable_list_t **head, int var_length,
									char *value, int value_length);
void check_environment_variable(variable_list_t **var_list, char *input,
								Shell_Info *data);
void free_variable_list(variable_list_t **head);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int (*get_builtin(char *cmd))(Shell_Info *datash);
int print_env(Shell_Info *shell);
int _isdigit(const char *c);
int _atoi(char *s);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
unsigned int _strlen(const char *s);
char *_strcpy(char *dest, char *src);
int exit_shell(Shell_Info *shell);
int cd_command(Shell_Info *shell);
int check_executable(Shell_Info *shell);
int execute_command(Shell_Info *shell);
char **tokenize_input(char *input);
int split_commands(Shell_Info *shell_info, char *input);
int get_error(Shell_Info *shell, int error_type);
char *error_env(Shell_Info *shell);
char *error_path(Shell_Info *shell);
char *error_not_found(Shell_Info *shell);
char *error_exit(Shell_Info *shell);
char *error_get_cd(Shell_Info *shell);
char *concat_cd(Shell_Info *shell, char *msg, char *error, char *counter);
separator_list_node_t *add_separator_node(separator_list_node_t **list_head,
						char separator);
commands_list_node_t *add_command_node(commands_list_node_t **list_head,
						char *command_line);
void add_sep_nodes(separator_list_node_t **head_s, char *input);
void add_command_nodes(commands_list_node_t **head_c, char *input);
void convert_special_chars(char *input, int bool);
char *find_command_path(char *command_name, char **envp);
int is_current_dir(char *path, int *i);
int check_error_access(char *dir, Shell_Info *shell);
void go_to_next_command(separator_list_node_t **list_s,
						commands_list_node_t **list_l, Shell_Info *datash);
void free_separation_list(separator_list_node_t **head);
void free_commands_list(commands_list_node_t **head);
int execute_external_command(Shell_Info *shell);
int repeated_char(char *input);
char *_getenv(const char *name, char **_environ);
char **realloc_double_pointer(char **ptr, unsigned int old_size,
								unsigned int new_size);
void add_nodes(separator_list_node_t **head_s, commands_list_node_t **head_c,
				char *input);
#endif
