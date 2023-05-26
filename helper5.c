#include "shell.h"

/**
 * realloc_double_pointer - reallocates a memory block for double ptr.
 * @ptr: double ptr to the memory previously allocated.
 * @old_size: old size
 * @new_size: new size.
 * Return: a ptr
 */
char **realloc_double_pointer(char **ptr, unsigned int old_size,
				unsigned int new_size)
{
	char **new_ptr;
	unsigned int i;

	if (ptr == NULL)
	{
		return (malloc(sizeof(char *) * new_size));
	}

	if (new_size == old_size)
	{
		return (ptr);
	}
	new_ptr = malloc(sizeof(char *) * new_size);
	if (new_ptr == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < old_size; i++)
	{
		new_ptr[i] = ptr[i];
	}
	free(ptr);
	return (new_ptr);
}
/**
 * _isdigit - Checks if a string is of decimal digits.
 *
 * @c:  The string to check.
 * Return: 1 if the character is a decimal digit, 0 otherwise.
 */
int _isdigit(const char *c)
{
	int i;

	for (i = 0; c[i]; i++)
	{
		if (c[i] < '0' || c[i] > '9')
		{
			return (0);
		}
	}
	return (1);
}
/**
 * repeated_char - counts the repetitions of a char
 *
 * @input: input string
 * Return: the repetitions
 */
int repeated_char(char *input)
{
	int i;

	for (i = 0; *(input - 1) == *input; input--, i++)
		continue;
	return (i);
}

/**
 * compare_env - compares the env var names
 * with the name passed.
 * @env_name: name of the environment variable
 * @name: the name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int compare_env(const char *env_name, const char *name)
{
	int i;

	for (i = 0; env_name[i] != '='; i++)
	{
		if (env_name[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}
/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if found, or NULL if not found.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr;
	int i, mov;

	ptr = NULL;
	mov = 0;
	for (i = 0; _environ[i]; i++)
	{
		mov = compare_env(_environ[i], name);
		if (mov)
		{
			ptr = _environ[i];
			break;
		}
	}

	return (ptr + mov);
}
