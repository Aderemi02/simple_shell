#include "shell.h"

/**
 * exec - executing a commanf in child process
 * @a1: list of arguments
 * @beginning: pointer to beginning of argument
 * Return: rep on success
 */
int exec(char **a1, char **beginning)
{
	pid_t sub_pid;
	int init, flag = 0, rep = 0;
	char *comm = a1[0];

	if (comm[0] != '/' && comm[0] != '.')
	{
		flag = 1;
		comm = loc(comm);
	}
	if (!comm || (access(comm, F_OK) == -1))
	{
		if (errno == EACCES)
			rep = (create_error(a1, 126));
		else
			rep = (create_error(a1, 127));
	}
	else
	{
		sub_pid = fork();
		if (sub_pid == -1)
		{
			if (flag)
				free(comm);
			perror("Error child:");
			return (1);
		}
		if (sub_pid == 0)
		{
			executeAndFree(rep, comm, a1, beginning);
		}
		else
		{
			wait(&init);
			rep = WEXITSTATUS(init);
		}
	}
	if (flag)
		free(comm);
	return (rep);
}

/**
 * executeAndFree - execute and free
 * @rep: input int representation
 * @comm: input char
 * @a1: input char
 * @beginning: starting of ther command
 * Return: 0 on success
 */
void executeAndFree(int rep, char *comm, char **a1, char **beginning)
{
	execve(comm, a1, environ);
	if (errno == EACCES)
		rep = (create_error(a1, 126));
	freeingenvir();
	free_arguments(a1, beginning);
	free_al_lst(global_alias);
	exit(rep);
}
/**
 * unable - printing error if file doesnt exist or error
 * @file: path to the file to
 * Return: 0 on success
 */
int unable(char *file)
{
	char *err, *history_str;
	int length;

	history_str = _itoa(global_history);
	if (!history_str)
		return (0);

			length = _strlen(source) + _strlen(history_str) + _strlen(file) + 16;
			err = malloc(sizeof(char) * (length + 1));

			if (!err)
			{
				free(history_str);
				return (0);
			}
			_strcpy(err, source);
			_strcat(err, ": ");
			_strcat(err, history_str);
			_strcat(err, ": can't open ");
			_strcat(err, file);
			_strcat(err, "\n");
			free(history_str);
			write(STDERR_FILENO, err, length);
			free(err);
			return (0);
}

/**
 * file_comm - runs a command in a file
 * @file: path to get to the file
 * @addrep: valuce of last command
 * Return: value of last command
 */
int file_comm(char *file, int *addrep)
{
	ssize_t fd, rd, i;
	char buff[120], *readline;
	unsigned int former = 120, new = 0;

	global_history = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		*addrep = unable(file);
		return (*addrep);
	}
	readline = malloc(sizeof(char) * former);
	if (!readline)
		return (-1);
	while (rd)
	{
		rd = read(fd, buff, 119);
		if (rd == 0 && new == 0)
			return (*addrep);
		buff[rd] = '\0';
		new = new + rd;
		readline = reallocation(readline, former, new);
		_strcat(readline, buff);
		former = new;
	}
	for (i = 0; readline[i] == '\n'; i++)
		readline[i] = ' ';
	for (; i < new; i++)
	{
		if (readline[i] == '\n')
		{
			readline[i] = ';';
			for (i += 1; i < new && readline[i] == '\n'; i++)
				readline[i] = ' ';
		}
	}
	return (splitCallAndFree(i, readline, addrep, new));
}

/**
 * splitCallAndFree - splits calls and free
 * @i: input int
 * @readline: input line to read
 * @addrep: input used to add rep
 * @new: input int
 * Return: 0 on success
 */
int splitCallAndFree(ssize_t i, char *readline, int *addrep, unsigned int new)
{
	int rep;
	char **args, **beginning;

	replace_env(&readline, addrep);
	split_line(&readline, new);
	args = _strtok(readline, " ");
	free(readline);
	if (!args)
		return (0);
	if (check_arguments(args) != 0)
	{
		*addrep = 2;
		free_arguments(args, args);
		return (*addrep);
	}
	beginning = args;
	i = 0;
	while (args[i])
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			rep = call_arguments(args, beginning, addrep);
			args = &args[++i];
			i = 0;
		}
		i++;
	}
	rep = call_arguments(args, beginning, addrep);
	free(beginning);
	return (rep);
}
