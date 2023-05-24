#include "shell.h"

/**
 * get_arguments - gets a command from input
 * @line: buffer to store the command
 * @last_command: last executed command return value
 * Return: a pointer to the stored command, if an error occurrents returns NULL
 */
char *get_arguments(char *line, int *last_command)
{
	size_t i = 0;
	ssize_t read;
	char *prompt = "cisfun$ ";

	if (line)
		free(line);

	read = _getline(&line, &i, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		global_history++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 8);
		return (get_arguments(line, last_command));
	}

	line[read - 1] = '\0';
	replace_env(&line, last_command);
	split_line(&line, read);

	return (line);
}

/**
 * call_arguments - splits operators from commands and calls them.
 * @args: arguments array
 * @beginning: pointer to the beginning of args
 * @last_command: last executed command return value
 * Return: The return value of the last executed command
 */
int call_arguments(char **args, char **beginning, int *last_command)
{
	int command_return, index;

	if (!args[0])
		return (*last_command);
	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_alias(args);
			command_return = run_arguments(args, beginning, last_command);
			if (*last_command != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (command_return);
			}
		}
		else if (_strncmp(args[index], "&&", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_alias(args);
			command_return = run_arguments(args, beginning, last_command);
			if (*last_command == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (command_return);
			}
		}
	}
	args = replace_alias(args);
	command_return = run_arguments(args, beginning, last_command);
	return (command_return);
}

/**
 * run_arguments - Calls the execution of a command.
 * @args: An array of arguments.
 * @beginning: A double pointer to the beginning of args.
 * @last_command: last executed command return value
 * Return: value of the last executed command.
 */
int run_arguments(char **args, char **beginning, int *last_command)
{
	int command_return, i;
	int (*builtin_func)(char **args, char **beginning);

	builtin_func = get_builtin_func(args[0]);

	if (builtin_func)
	{
		command_return = builtin_func(args + 1, beginning);
		if (command_return != EXIT_CODE)
			*last_command = command_return;
	}
	else
	{
		*last_command = exec(args, beginning);
		command_return = *last_command;
	}

	global_history++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (command_return);
}

/**
 * handle_arguments - Gets, calls, and runs the execution of a command.
 * @last_command: last executed command return value
 * Return: if end-of-file is -2, if cant split -1 else 0
 */
int handle_arguments(int *last_command)
{
	int command_return = 0, index;
	char **args, *line = NULL, **beginning;

	line = get_arguments(line, last_command);
	if (!line)
		return (EOF_CODE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (command_return);
	if (check_arguments(args) != 0)
	{
		*last_command = 2;
		free_arguments(args, args);
		return (*last_command);
	}
	beginning = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			command_return = call_arguments(args, beginning, last_command);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		command_return = call_arguments(args, beginning, last_command);

	free(beginning);
	return (command_return);
}

/**
 * check_arguments - checks if there are any leading ';', ';;', '||', or '&&'.
 * @args: 2D pointer to tokenized commands and arguments
 * Return: 2 if a ';', '&&', or '||' is placed at an invalid position else 0
 */
int check_arguments(char **args)
{
	size_t i;
	char *current, *next;

	for (i = 0; args[i]; i++)
	{
		current = args[i];
		if (current[0] == ';' || current[0] == '&' || current[0] == '|')
		{
			if (i == 0 || current[1] == ';')
				return (create_error(&args[i], 2));
			next = args[i + 1];
			if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
				return (create_error(&args[i + 1], 2));
		}
	}
	return (0);
}
