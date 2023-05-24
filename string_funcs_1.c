#include "shell.h"
/**
 * _strlen - prints the length of the array
 * @s: a pointer the character we want to get it`s length
 *
 * Return: length 'a'
 */
int _strlen(char *s)
{
	int a = 0;

	while (*s != '\0')
	{
		a++;
		s++;
	}
	return (a);
}

/**
 * _strcmp - compare two strings
 * @s1: the first string
 * @s2: the second string
 *
 * Return: returns value.
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
		return (0);
}

/**
 * _strncmp - compare two strings
 * @s1: the first string
 * @s2: the second string
 * @n: number of strings to be compared
 * Return: returns value.
 */
int _strncmp(char *s1, char *s2, size_t n)
{
	size_t i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] > s2[i])
		{
			return (s1[i] - s2[i]);
		}
		else if (s1[i] < s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	if (i == n)
		return (0);
	else
		return (-1);
}

/**
 * *_strcat - to concatenate two strings
 * @dest: destination string
 * @src: source string
 * Return: return destination string
 */

char *_strcat(char *dest, char *src)
{
	int i = 0;
	int destlen = 0;

	while (dest[destlen] != '\0')
	{
		destlen++;
	}

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[destlen + i] = src[i];
	}
	dest[destlen + i] = '\0';
	return (dest);
}

/**
 * *_strncat - to concatenate two strings
 * @dest: the destination string
 * @src: the source string
 * @n: number of source byte
 * Return: return destination string
 */

char *_strncat(char *dest, char *src, int n)
{
	int i = 0;
	int destlen = 0;

	while (dest[destlen] != '\0')
	{
		destlen++;
	}

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[destlen + i] = src[i];
	}

	return (dest);
}
