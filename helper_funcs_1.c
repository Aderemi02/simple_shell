#include "shell.h"


/**
 * free_arguments - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @beginning: pointer to the beginning of args
 */
void free_arguments(char **args, char **beginning)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(beginning);
}

/**
 * get_pid - gets current process ID.
 * Return: current process ID or NULL if fails.
 */
char *get_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_environ_value - gets the value corresponding to an environmental var.
 * @source: environmental variable source to search.
 * @len: environmental variable lenght.
 * Return: the variable and empty string if not found
 */
char *get_environ_value(char *source, int len)
{
	char **var_addr;
	char *replace_env = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, source, len);

	var_addr = gettingenvir(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replace_env = malloc(_strlen(temp) + 1);
		if (replace_env)
			_strcpy(replace_env, temp);
	}

	return (replace_env);
}

/**
 * replace_env - used to replace the environmental variable
 * @line: pointer that has arguments and commands
 * @last_command: pointer to the return value of the last executed command.
 */
void replace_env(char **line, int *last_command)
{
	int j, k = 0, len;
	char *replace_env = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
				old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replace_env = get_pid();
				k = j + 2;
			} else if (old_line[j + 1] == '?')
			{
				replace_env = _itoa(*last_command);
				k = j + 2;
			} else if (old_line[j + 1])
			{
				for (k = j + 1; old_line[k] && old_line[k] != '$' &&
						old_line[k] != ' '; k++)
					;
				len = k - (j + 1);
				replace_env = get_environ_value(&old_line[j + 1], len);
			} new_line = malloc(j + _strlen(replace_env)
					+ _strlen(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, j);
			if (replace_env)
			{
				_strcat(new_line, replace_env), free(replace_env);
				replace_env = NULL;
			}
			_strcat(new_line, &old_line[k]);
			free(old_line),	*line = new_line;
			old_line = new_line, j = -1;
		}
	}
}
