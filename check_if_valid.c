#include "shell.h"

/* helper functions */

/**
 * verify_path - return 1 if path is valid, 0 otherwise
 * @path: string
 * Return: int
 */
int verify_path(path)
{
	/*temp implementation*/
	return (1);
}
/**
 * verify_options - return 1 if options are valid, 0 otherwise
 * @options: string
 * Return: int
 */
int verify_options(options)
{
	/*temp implementation*/
	return (1);
}
/**
 * verify_rest - return 1 if rest is valid, 0 otherwise
 * @rest: string
 * Return: int
 */
int verify_rest(rest)
{
	/*temp implementation*/
	return (1);
}
/* the function to be called */
/**
 * check_if_valid - return 1 if all info is valid, 0 otherwise
 * @cmd: an object of type struct INFO_t
 * Return: int
 */
int check_if_valid(INFO_t *cmd)
{
	char *path = cmd->path, *options = cmd->options, *rest = cmd->rest;

	if (!verify_path(path))
		return (0)
	if (!verify_options(options))
		return (-1);
	if (!verify_rest(rest))
		return (-2);
	return (1);
}
