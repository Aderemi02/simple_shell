#include "shell.h"

/**
 * builtin_alias - builtin command  used to print all global_alias or set alias
 * @args: arguments array
 * @beginning: pointer to the beginning of the arguments passed
 * Return: 0 and -1 if has error
 */
int builtin_alias(char **args, char __attribute__((__unused__)) **beginning)
{
	new_alias *temp_alias = global_alias;
	int i, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp_alias)
		{
			print_alias(temp_alias);
			temp_alias = temp_alias->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		temp_alias = global_alias;
		value = _strchr(args[i], '=');
		if (!value)
		{
			while (temp_alias)
			{
				if (_strcmp(args[i], temp_alias->source) == 0)
				{
					print_alias(temp_alias);
					break;
				}
				temp_alias = temp_alias->next;
			}
			if (!temp_alias)
				ret = create_error(args + i, 1);
		}
		else
			set_alias(args[i], value);
	}
	return (ret);
}

/**
 * set_alias - sets an existing alias 'source' with a new value
 * @source: alias source
 * @value: alias value
 */
void set_alias(char *source, char *value)
{
	new_alias *temp_alias = global_alias;
	int len, j, k;
	char *new_value;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[k++] = value[j];
	}
	new_value[k] = '\0';
	while (temp_alias)
	{
		if (_strcmp(source, temp_alias->source) == 0)
		{
			free(temp_alias->value);
			temp_alias->value = new_value;
			break;
		}
		temp_alias = temp_alias->next;
	}
	if (!temp_alias)
		add_end_alias(&global_alias, source, new_value);
}
/**
 * replace_alias - replaces any matching alias
 * @args: arguments passed.
 * Return: char pointer to the arguments.
 */
char **replace_alias(char **args)
{
	new_alias *temp_alias;
	int i;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		temp_alias = global_alias;
		while (temp_alias)
		{
			if (_strcmp(args[i], temp_alias->source) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(temp_alias->value) + 1));
				if (!new_value)
				{
					free_arguments(args, args);
					return (NULL);
				}
				_strcpy(new_value, temp_alias->value);
				free(args[i]);
				args[i] = new_value;
				i--;
				break;
			}
			temp_alias = temp_alias->next;
		}
	}

	return (args);
}
/**
 * print_alias - prints alias in source to value format.
 * @alias: pointer to alias.
 */
void print_alias(new_alias *alias)
{
	char *alias_string;
	int len = _strlen(alias->source) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->source);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}


