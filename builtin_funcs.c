#include "shell.h"

/**
 * get_builtin_func - looks for builtin functions
 * @command: The command to check
 * Return: corresponding builtin function
 */
int (*get_builtin_func(char *command))(char **args, char **beginning)
{
	new_builtin builtin_funcs[] = {
		{ "cd", builtin_cd },
		{ "env", builtin_env },
		{ "exit", builtin_exit },
		{ "setenv", builtin_setenv },
		{ "unsetenv", builtin_unsetenv },
		{ "alias", builtin_alias },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin_funcs[i].source; i++)
	{
		if (_strcmp(builtin_funcs[i].source, command) == 0)
			break;
	}
	return (builtin_funcs[i].func);
}

/**
 * builtin_exit - builtin function that terminates the process shell process
 * @args: arguments array
 * @beginning: pointer to the beginning of the arguments passed
 * Return: -3 if there are no arguments, -2 if invalid 0 otherwise
 */
int builtin_exit(char **args, char **beginning)
{
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);
	int i, length = 10;

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			length++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= length && args[0][i] <= '9' && args[0][i] >= '0')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_arguments(args, beginning);
	freeingenvir();
	free_al_lst(global_alias);
	exit(num);
}

/**
 * builtin_cd - used to change the current directory
 * @args: arguments array
 * @beginning: pointer to the beginning of the arguments
 * Return: 2 if not a directory, -1 if contains error otherwise 0
 */
int builtin_cd(char **args, char __attribute__((__unused__)) **beginning)
{
	char **directory_details, *new_line = "\n";
	char *old_pwd = NULL, *pwd = NULL;
	struct stat source;

	old_pwd = getcwd(old_pwd, 0);
	if (!old_pwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (gettingenvir("OLDPWD") != NULL)
					(chdir(*gettingenvir("OLDPWD") + 7));
			}
			else
			{
				free(old_pwd);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &source) == 0 && S_ISDIR(source.st_mode)
					&& ((source.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(old_pwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (gettingenvir("HOME") != NULL)
			chdir(*(gettingenvir("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	directory_details = malloc(sizeof(char *) * 2);
	if (!directory_details)
		return (-1);

	directory_details[0] = "OLDPWD";
	directory_details[1] = old_pwd;
	if (builtin_setenv(directory_details, directory_details) == -1)
		return (-1);

	directory_details[0] = "PWD";
	directory_details[1] = pwd;
	if (builtin_setenv(directory_details, directory_details) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(old_pwd);
	free(pwd);
	free(directory_details);
	return (0);
}
