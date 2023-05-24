#ifndef CON_H
#define CON_H

#define INTERACTIVE_MODE 1
#define NOT_INTERACTIVE_PIPED_MODE 2
#define NOT_INTERACTIVE_MODE 3
#define INVALID_MODE_ERR 0
#define TOK_DELIM " \t\r\n\a"
#define MAX_PATH_LENGTH 1024
#define INPUT_BUFFER_SIZE 2048

/*Builtin confing*/
#define ENV_BUILTIN 0
#define EXIT_BUILTIN 1

/*Errors*/
#define EXIT_WITH_ERROR 2
#define NO_PERMISSION 126
#define NOT_FOUND 127

#endif
