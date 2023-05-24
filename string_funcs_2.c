#include "shell.h"
/**
 * _strchr - checking characters
 * @s: string to be compared
 * @c: character to be found
 * Return: Always 0 (Success)
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	while (s[i] >= '\0')
	{
		if (s[i] == c)
		{
			return (&s[i]);
		}
	i++;
	}
	return (0);
}

/**
 * *_strcpy - copy strings
 * @dest: - destination to be copied to
 * @src: - srouce string
 * Return: return dest.
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i++] = '\0';
	return (dest);
}

/**
 * _strspn - find the length of prefix string
 * @s: full string
 * @accept: string to check
 * Return: return i
 */

unsigned int _strspn(char *s, char *accept)
{
	unsigned int a, i = 0;

	while (*s)
	{
		for (a = 0; accept[a]; a++)
		{
			if (*s == accept[a])
		{
			i++;
			break;
		}
			else if (accept[a + 1] == '\0')
				return (i);
		}
		s++;
	}
	return (i);
}

/**
 * _strtok - this tokenizes the string inputed
 * @readline: the string passed
 * @delimit: the delimiter
 * Return: pointer cointaining the tokenised strings
 */
char **_strtok(char *readline, char *delimit)
{
	char **p;
	int ind = 0, token, tok, let, letter;

	token = counting_token(readline, delimit);
	if (token == 0)
		return (NULL);
	p = malloc(sizeof(char *) * (token + 2));
	if (!p)
		return (NULL);

	for (let = 0; let < token; let++)
	{
		while (readline[ind] == *delimit)
			ind++;

		letter = token_length(readline + ind, delimit);
		p[let] = malloc(sizeof(char) * (letter + 1));
		if (!p[let])
		{
			for (ind -= 1; ind >= 0; ind--)
				free(p[ind]);
			free(p);
			return (NULL);
		}

		for (tok = 0; tok < letter; tok++)
		{
			p[let][tok] = readline[ind];
			ind++;
		}
		p[let][tok] = '\0';
	}
	p[let] = NULL;
	p[let + 1] = NULL;
	return (p);
}
