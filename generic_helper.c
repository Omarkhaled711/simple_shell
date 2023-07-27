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
 * _realloc - similar to the realloc funtionin the stldib.h
 * @ptr: pointer to the existing memory
 * @old_size: old size
 * @new_size: new size
 * Return: a void pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i;
	void *p;
	char *access1, *access2;

	if (old_size == new_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	p = malloc(new_size);
	if (p == 0)
		return (NULL);
	access1 = p;
	access2 = ptr;
	if (old_size > new_size)
		old_size = new_size;
	for (i = 0; i < old_size && ptr != NULL; i++)
		access1[i] = access2[i];
	if (p != ptr)
		free(ptr);
	return (p);
}
