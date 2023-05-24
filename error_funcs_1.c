#include "shell.h"

/**
 * error_env - creates error message for builtin_env errors.
 * @args: arguments array passed as command.
 * Return: error string.
 */
char *error_env(char **args)
{
	char *error, *history_str;
	int len;

	history_str = _itoa(global_history);
	if (!history_str)
		return (NULL);

	args--;
	len = _strlen(source) + _strlen(history_str) + _strlen(args[0]) + 45;
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
	_strcat(error, ": Unable to add/remove from environment\n");

	free(history_str);
	return (error);
}

/**
 * error_alias - creates error message for builtin_alias errors.
 * @args: arguments array passed as command.
 * Return: error string.
 */
char *error_alias(char **args)
{
	char *error;
	int len;

	len = _strlen(source) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");

	return (error);
}

/**
 * error_exit - creates error message for builtin_exit errors.
 * @args: arguments array passed as command.
 * Return: error string.
 */
char *error_exit(char **args)
{
	char *error, *history_str;
	int len;

	history_str = _itoa(global_history);
	if (!history_str)
		return (NULL);

	len = _strlen(source) + _strlen(history_str) + _strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error, source);
	_strcat(error, ": ");
	_strcat(error, history_str);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(history_str);
	return (error);
}

/**
 * error_cd - creates error message for builtin_cd errors.
 * @args: arguments array passed as command.
 * Return: error string.
 */
char *error_cd(char **args)
{
	char *error, *history_str;
	int len;

	history_str = _itoa(global_history);
	if (!history_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
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
	if (args[0][0] == '-')
		_strcat(error, ": cd: Illegal option ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(history_str);
	return (error);
}

/**
 * error_syntax - creates error message for syntax errors.
 * @args: arguments array passed as command.
 * Return: error string.
 */
char *error_syntax(char **args)
{
	char *error, *history_str;
	int len;

	history_str = _itoa(global_history);
	if (!history_str)
		return (NULL);

	len = _strlen(source) + _strlen(history_str) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(history_str);
		return (NULL);
	}

	_strcpy(error, source);
	_strcat(error, ": ");
	_strcat(error, history_str);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" unexpected\n");

	free(history_str);
	return (error);
}
