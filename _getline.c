#include "shell.h"

/**
 * _getline - custom implementation of the getline function
 *
 * @string: a pointer to a string
 * @n: a pointer to size
 * @stream: a pointer to file
 *
 * Return: the same as getline
 */
size_t _getline(char **string, size_t *n, FILE *stream)
{
	return (getline(string, n, stream));
	/*
	 * For now I will be calling the getline from the inside of
	 * this function, so that when I come back to implementing it
	 * my self, I won't need to change the other parts of the code
	 */
}
