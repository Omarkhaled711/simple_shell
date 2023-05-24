#include "shell.h"

/**
 * _strlen - a function that returns the length of a string.
 *
 * @s: the string to find its length
 * Return: the length of s
 */
unsigned int _strlen(char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
	}
	return (i);
}
/**
 * _strdup -  a function that creates a string which contains a copy
 *		of the one given as a parameter.
 *
 * @str: the char to use to fill the array
 * Return: a pointer to str, or NULL if it fails
 */
char *_strdup(char *str)
{
	int i;
	char *s;

	if (str == NULL)
	{
		return (NULL);
	}
	for (i = 0; str[i]; i++)
	{
	}
	i++;
	s = (char *) malloc(sizeof(char) * i);
	if (s == NULL)
	{
		return (NULL);
	}

	for (i = 0; str[i] ; i++)
	{
		s[i] = str[i];
	}
	s[i] = 0;
	return (s);
}
/**
 * _strcmp - a function that compares two strings.
 *
 * @s1: first string
 * @s2: second string
 * Return: int
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i]; i++)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
	}
	return (s1[i] - s2[i]);
}
/**
 * free_string_array - frees an array of strings allocated with malloc()
 * @array: pointer to the array of strings
 */
void free_string_array(char **array)
{
	unsigned int i;

	if (array == NULL)
	{
		return;
	}

	for (i = 0; array[i]; i++)
	{
		free(array[i]);
	}

	free(array);
}
/**
 * _atoi - convert number inside a string into int
 *
 * @s: string that contains the number
 * Return: the integer if it exists or 0 otherwise
 */


int _atoi(char *s)
{
	int neg = 0, i, ans = 0;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < '0' || s[i] > '9')
		{
			if (ans != 0)
			{
				break;
			}
			if (s[i] == '-')
			{
				neg++;
			}
		}
		else if (s[i] >= '0' && s[i] <= '9')
		{
			ans *= 10;
			ans -= s[i] - '0';
		}
	}
	if (neg % 2 == 0)
	{
		ans = -ans;
	}
	return (ans);
}
