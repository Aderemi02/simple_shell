#include "shell.h"

/**
 * split_line - splits a line read from standard input as needed.
 * @line: A pointer to a line read from standard input.
 * @read: The length of line.
 */
void split_line(char **line, ssize_t read)
{
	char *old_line, *new_line, prev, current, next;
	size_t i, j = 0;
	int result;
	ssize_t new_length;

	new_length = get_line_length(*line);
	if (new_length == read - 1)
		return;
	new_line = malloc(new_length + 1);
	if (!new_line)
		return;
	old_line = *line;
	for (i = 0; old_line[i]; i++)
	{
		current = old_line[i];
		next = old_line[i + 1];
		if (i != 0)
		{
			result = splitForOthers(i, j, prev, next, old_line, new_line);
			if (result == 0)
				continue;
		}
		else if (current == ';')
		{
			result = split_other_column(i, j, next, new_line);
			if (result == 0)
				continue;
		}
		new_line[j++] = old_line[i];
	}
	new_line[j] = '\0';
	free(*line);
	*line = new_line;
}

/**
 * get_line_length - gets new length of the splitted line
 * Return: new length of the line.
 */
ssize_t get_line_length(char *line)
{
	size_t i;
	ssize_t new_length = 0;
	char current, next;

	for (i = 0; line[i]; i++)
	{
		current = line[i];
		next = line[i + 1];
		if (current == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					new_length += 2;
					continue;
				}
				else if (line[i - 1] == ';' && next != ' ')
				{
					new_length += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					new_length++;
				if (next != ' ')
					new_length++;
			}
			else
				check_operator(&line[i], &new_length);
		}
		else if (current == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				new_length++;
			if (next != ' ' && next != ';')
				new_length++;
		}
		new_length++;
	}
	return (new_length);
}
/**
 * check_operator - checks a line for logical operators like "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_length: Pointer to new_length in get_line_length function.
 */
void check_operator(char *line, ssize_t *new_length)
{
	char prev, current, next;

	prev = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && prev != ' ')
			(*new_length)++;
		else if (prev == '&' && next != ' ')
			(*new_length)++;
	}
	else if (current == '|')
	{
		if (next == '|' && prev != ' ')
			(*new_length)++;
		else if (prev == '|' && next != ' ')
			(*new_length)++;
	}
}
