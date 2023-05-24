#include "shell.h"

/**
 * error_126 - creates error message for permission denied errors
 * @args: arguments array passed as command.
 * Return: error string.
 */
char *error_126(char **args)
{
	char *error, *history_str;
	int len;

	history_str = _itoa(global_history);
	if (!history_str)
		return (NULL);

	len = _strlen(source) + _strlen(history_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error, source);
	_strcat(error, ": ");
	_strcat(error, history_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(history_str);
	return (error);
}

/**
 * error_127 - creates error message for command not found errors
 * @args: arguments array passed as command.
 * Return: error string.
 */
char *error_127(char **args)
{
	char *error, *history_str;
	int len;

	history_str = _itoa(global_history);
	if (!history_str)
		return (NULL);

	len = _strlen(source) + _strlen(history_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error, source);
	_strcat(error, ": ");
	_strcat(error, history_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(history_str);
	return (error);
}
