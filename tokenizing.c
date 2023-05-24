#include "shell.h"
/**
 * counting_token - counting the number of token in a string
 * @s1: strings with the token
 * @delimit: delimiter to separate each token
 * Return: tokens
 */
int counting_token(char *s1, char *delimit)
{
	int ind, token, length = 0;

	for (ind = 0; *(s1 + ind); ind++)
	{
		length++;
	}

	ind = 0;
	token = 0;

	while (ind < length)
	{
		if (*(s1 + ind) != *delimit)
		{
			token++;
			ind += token_length(s1 + ind, delimit);
		}
		ind++;
	}
	return (token);
}

/**
 * token_length - length of the token on getting to a delimiter
 * @s1: strings to be counted to reach a dlimiter
 * @delimit: delimiter to truncate a string
 * Return: length of the token in a string
 */
int token_length(char *s1, char *delimit)
{
	int ind, length = 0;

	for (ind = 0; (*(s1 + ind) && *(s1 + ind) != *delimit); ind++)
	{
		length++;
	}
	return (length);
}

