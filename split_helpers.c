#include "shell.h"

/**
 * splitForOthers - splits a line column
 * @prev: prev char
 * @current: current char
 * @next: next char
 * @new_line: new_line
 * @old_line: old line
 * @i: input int
 * @j: input int
 * Return: result
 */
int splitForOthers(size_t i, size_t j, char prev, char current, char next, char *old_line, char* new_line)
{
    prev = old_line[i - 1];
	if (current == ';')
	{
		return (split_column(i, j, prev, next, new_line));
	}
	else if (current == '&')
	{
		return (split_and(i, j, prev, next, new_line));
	}
	else if (current == '|')
	{
		return (split_pipe(i, j, prev, next, new_line));
	}
}
/**
 * split_other_column - splits a line column
 * @next: next char
 * @old_line: old line
 * @i: input int
 * @j: input int
 * Return: result
 */
int split_other_column(size_t i, size_t j, char next, char *old_line)
{
	if (i != 0 && old_line[i - 1] != ' ')
		new_line[j++] = ' ';
	new_line[j++] = ';';
	if (next != ' ' && next != ';')
		new_line[j++] = ' ';
	return (0);
}
/**
 * split_pipe - splits a line pipe
 * @prev: prev char
 * @next: next char
 * @new_line: new line
 * @i: input int
 * @j: input int
 * Return: result
 */
int split_pipe(size_t i, size_t j, char prev, char next, char *new_line)
{
	if (next == '|' && prev != ' ')
		new_line[j++]  = ' ';
	else if (prev == '|' && next != ' ')
	{
		new_line[j++] = '|';
		new_line[j++] = ' ';
		return (0);
	}
	return (1);
}
/**
 * split_and - splits a line and
 * @prev: prev char
 * @next: next char
 * @new_line: new line
 * @i: input int
 * @j: input int
 * Return: result
 */
int split_and(size_t i, size_t j, char prev, char next, char *new_line)
{
	if (next == '&' && prev != ' ')
		new_line[j++] = ' ';
	else if (prev == '&' && next != ' ')
	{
		new_line[j++] = '&';
		new_line[j++] = ' ';
		return (0);
	}
	return (1);
}
/**
 * split_column - splits a line column
 * @prev: prev char
 * @next: next char
 * @new_line: new line
 * @i: input int
 * @j: input int
 * Return: result
 */
int split_column(size_t i, size_t j, char prev, char next, char *new_line)
{
	if (next == ';' && prev != ' ' && prev != ';')
	{
		new_line[j++] = ' ';
		new_line[j++] = ';';
		return (0);
	}
	else if (prev == ';' && next != ' ')
	{
		new_line[j++] = ';';
		new_line[j++] = ' ';
		return (0);
	}
	if (prev != ' ')
		new_line[j++] = ' ';
	new_line[j++] = ';';
	if (next != ' ')
		new_line[j++] = ' ';
	return (0);
}
