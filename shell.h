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
#include "config.h"

/*Structs*/
/**
 * struct Path_Dir - singly linked list
 * @path: string
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct Path_Dir
{
	char *path;
	unsigned int len;
	struct Path_Dir *next;
} Path_Dir;

/**
 * struct Argv - holds the cmd args and their count
 *
 * @argv: the args
 * @argc: their count
 */

typedef struct Argv
{
char **argv;
unsigned int argc;
} Argv;

/**
 * struct Shell_Info - a struct that holds shell info
 *
 * @PATH: the list of path directories
 * @name: the name of the program
 * @counter: the counter
 * @status: the status
 */
typedef struct Shell_Info
{
	Path_Dir *PATH;
	char *name;
	int counter;
	int status;
} Shell_Info;
/*extern the enivon variable so that all c files can access it*/
extern char **environ;
/*starting functions*/
void start_interactive(Shell_Info *current, char *env[]);
void start_non_interactive(int mode, Shell_Info *current,
							char **env, char **argv);

/*string functions*/
char *_strdup(char *str);
unsigned int _strlen(char *s);
int _strcmp(char *s1, char *s2);
void free_string_array(char **array);
int _atoi(char *s);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_memcpy(char *dest, char *src, unsigned int n);
char **_strsplit(char *str, char *delim);

/*struct Path_Dir functions*/
Path_Dir *get_path_directories();
Path_Dir *append_directory_node(Path_Dir *list, Path_Dir *node);
Path_Dir *create_directory_node(char *path);
void free_path_list(Path_Dir *head);

/*general functions*/
int get_mode(int argc);
char *read_command(Path_Dir *PATH);
char **format_command(char *command, int status);
void remove_comments(char *command);
char *get_process_id();
char *get_status(int status);
void execute_builtin(int choose, char *command, char **formatted,
						Shell_Info *current);
void print_env(void);
void execute_exit(char *command, char **formatted, Shell_Info *current);
char *num_to_string(int num);
int is_directory(char *file);
void process_command(char **formatted, char *env[], Shell_Info *current);
char *check_PATH(char *command, Path_Dir *PATH);
char *_getenv(const char *name);
void print_error_header(char *name, int counter);
void print_error(Shell_Info *current, char *command, int error_type);
void run_command(char *path, char **command, char **env, int status);
int check_builtin(char *cmd);
char **get_non_interactive_commands(int mode, char *argv[]);
char **get_from_piped();
char **get_from_file(char *file_name, char *program_name);
char *read_file(int file_descriptor, size_t file_size);
void print_file_open_problem(char *program_name, char *file_name);

#endif
