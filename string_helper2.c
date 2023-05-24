#include "shell.h"

/**
 * _strcat - a function that concatenates two strings.
 *
 * @dest: pointer to the destination string
 * @src: pointer to the second string
 * Return: pointer to the destination
 */
char *_strcat(char *dest, char *src)
{
	int i, j;

	for (i = 0; dest[i]; i++)
	{
	}
	for (j = 0; src[j]; i++, j++)
	{
		dest[i] = src[j];
	}
	dest[i] = 0;
	return (dest);
}
/**
 * _strcpy - a function that copies a string.
 *
 * @dest: the destination where u want ur string to be copied
 * @src: the original string
 * Return: pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int  i = 0;

	for (i = 0; src[i]; i++)
	{
		dest[i] = src[i];

	}
	dest[i] = 0;
	return (dest);
}
/**
 * _memcpy - The _memset() function copies the first n bytes from src to dest
 *
 * @dest: pointer to a char
 * @src: pointer to a char
 * @n: number bytes
 * Return: pointer to dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}
/**
 * _strsplit - splits a text when facing a certain char
 *
 * @str: the string
 * @delim:  the char that will cause the string to split
 * Return: char**
 */
char **_strsplit(char *str, char *delim)
{
	char **tokens = NULL;
	char *token;
	unsigned int num_tokens = 0, i = 0;

	for (token = strtok(str, delim); token != NULL; token = strtok(NULL, delim))
	{
		num_tokens++;
	}
	tokens = malloc(sizeof(char *) * num_tokens);
	if (tokens == NULL)
	{
		return (NULL);
	}
	for (token = strtok(str, delim); token != NULL; token = strtok(NULL, delim))
	{
		tokens[i] = token;
		i++;
	}
	return (tokens);
}
