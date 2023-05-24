#include "shell.h"
/**
 * reallocation - reallocating memory
 * @p: pointer to former memory
 * @former: size of former memory
 * @nw: size of new memory
 * Return: memory reallocated
 */
void *reallocation(void *p, unsigned int former, unsigned int nw)
{
	void *memory;
	char *p_cpy, *fill;
	unsigned int ind;

	if (nw == former)
		return (p);

	if (p == NULL)
	{
		memory = malloc(nw);
		if (memory == NULL)
			return (NULL);

		return (memory);
	}

	if (nw == 0 && p != NULL)
	{
		free(p);
		return (NULL);
	}
	p_cpy = p;
	memory = malloc(sizeof(*p_cpy) * nw);
	if (memory == NULL)
	{
		free(p);
		return (NULL);
	}
	fill = memory;
	ind = 0;

	while (ind < former && ind < nw)
	{
		fill[ind] = *p_cpy++;
		ind++;
	}
	free(p);
	return (memory);
}

/**
 * _getline - reads an input string from a stream
 * @ptr: stores the input string
 * @num: size of ptr
 * @stream: file to read
 * Return: rep on success
 */
ssize_t _getline(char **ptr, size_t *num, FILE *stream)
{
	static ssize_t pass;
	ssize_t rep;
	char *buff, prt = 'x';
	int p;

	if (pass == 0)
		fflush(stream);
	else
		return (-1);
	pass = 0;
	buff = malloc(sizeof(char) * 120);
	if (!buff)
		return (-1);

	for (; prt != '\n'; pass++)
	{
		p = read(STDIN_FILENO, &prt, 1);
		if (p == -1 || (p == 0 && pass == 0))
		{
			free(buff);
			return (-1);
		}
		if (p == 0 && pass != 0)
		{
			pass++;
			break;
		}
		if (pass >= 120)
		{
			buff = reallocation(buff, pass, pass + 1);
		}
		buff[pass] = prt;
	}
	buff[pass] = '\0';
	assigning(ptr, num, buff, pass);
	rep = pass;

	if (p != 0)
		pass = 0;
	return (rep);
}

/**
 * assigning - reassigns prt for getline
 * @ptr: an input string
 * @num: size of ptr
 * @buff: buffer to assign the string to
 * @pass: size of buffer
 */
void assigning(char **ptr, size_t *num, char *buff, size_t pass)
{
	if (*ptr == NULL)
	{
		if (pass > 120)
			*num = pass;
		else
			*num = 120;
		*ptr = buff;
	}
	else if (*num < pass)
	{
		if (pass > 120)
			*num = pass;
		else
			*num = 120;
		*ptr = buff;
	}
	else
	{
		_strcpy(*ptr, buff);
		free(buff);
	}
}
