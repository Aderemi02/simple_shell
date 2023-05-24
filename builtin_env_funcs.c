#include "shell.h"

/**
 * builtin_env - prints all the current environment variables
 * @args: arguments array passed to shell
 * @beginning: pointer to the beginning of the arguments passed
 * Return: 0 if success else -1
 */
int builtin_env(char **args, char __attribute__((__unused__)) **beginning)
{
	int index;
	char new_line = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
		write(STDOUT_FILENO, &new_line, 1);
	}

	(void)args;
	return (0);
}

/**
 * builtin_setenv - adds or changes an environmental variable to the PATH.
 * @args: arguments array passed to shell
 * @beginning: pointer to the beginning of the arguments passed
 * Return: 0 if success else -1
 */
int builtin_setenv(char **args, char __attribute__((__unused__)) **beginning)
{
	char **env = NULL, **new_environ, *new_value;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (create_error(args, -1));
	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (create_error(args, -1));
	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);
	env = gettingenvir(args[0]);
	if (env)
	{
		free(*env);
		*env = new_value;
		return (0);
	}
	size = 0;
	while (environ[size])
	{
		size++;
	}
	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (create_error(args, -1));
	}
	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];
	free(environ);
	environ = new_environ;
	environ[index] = new_value;
	environ[index + 1] = NULL;

	return (0);
}

/**
 * builtin_unsetenv - remove an environmental
 * variable from the PATH.
 * @args: arguments array passed to shell
 * @beginning: pointer to the beginning of the
 * arguments passed
 * Return: 0 if success else -1
 */
int builtin_unsetenv(char **args, char __attribute__((__unused__)) **beginning)
{
	char **env, **new_environ;
	size_t size;
	int index, index2;

	if (!args[0])
		return (create_error(args, -1));
	env = gettingenvir(args[0]);
	if (!env)
		return (0);
	size = 0;
	while (environ[size])
	{
		size++;
	}
	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_error(args, -1));
	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (*env == environ[index])
		{
			free(*env);
			continue;
		}
		new_environ[index2] = environ[index];
		index2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
