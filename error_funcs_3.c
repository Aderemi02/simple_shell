#include "shell.h"

/**
 * num_len - Counts the digit length of a number.
 * @num: number to measure
 * Return: The number length
 */
int num_len(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 /= 10;
	}

	return (len);
}

/**
 * _itoa - Converts an integer to a string.
 * @num: number passed
 * Return: error string.
 */
char *_itoa(int num)
{
	char *buffer;
	int len = num_len(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}


/**
 * create_error - prints custom error message to stderr
 * @args: arguments array
 * @error_code: error value
 * Return: error
 */
int create_error(char **args, int error_code)
{
	char *error;

	switch (error_code)
	{
	case -1:
		error = error_env(args);
		break;
	case 1:
		error = error_alias(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = error_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = error_syntax(args);
		else
			error = error_cd(args);
		break;
	case 126:
		error = error_126(args);
		break;
	case 127:
		error = error_127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (error_code);

}
