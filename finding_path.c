#include "shell.h"
/**
 * loc - locating a command in  a path
 * @comm: the command string
 * Return: pathname of command on success
 */
char *loc(char *comm)
{
	char **find, *temp;
	new_list *directs, *head;
	struct stat start;

	find = gettingenvir("PATH");
	if (!find || !(*find))
		return (NULL);

	directs = get_direction(*find + 5);
	head = get_direction(*find + 5);

	while (directs)
	{
		temp = malloc(_strlen(directs->source) + _strlen(comm) + 2);
		if (!temp)
			return (NULL);

		_strcpy(temp, directs->source);
		_strcat(temp, "/");
		_strcat(temp, comm);

		if (stat(temp, &start) == 0)
		{
			freeinglst(head);
			return (temp);
		}
		directs = directs->next;
		free(temp);
	}
	freeinglst(head);
	return (NULL);
}

/**
 * get_direction - getting the path direction
 * @find: list of directories
 * Return: pointer to the beginning of the list
 */
new_list *get_direction(char *find)
{
	int ind = 0;
	new_list *head = NULL;
	char **directs, *find_dup;

	find_dup = fill_direction(find);
	if (!find_dup)
		return (NULL);
	directs = _strtok(find_dup, ":");
	free(find_dup);

	if (!directs)
		return (NULL);

	while (directs[ind])
	{
		if (add_end_node(&head, directs[ind]) == NULL)
		{
			freeinglst(head);
			free(directs);
			return (NULL);
		}
		ind++;
	}
	free(directs);
	return (head);
}

/**
 * fill_direction - fills the path direction
 * @find: list of the directories
 * Return: filled path
 */
char *fill_direction(char *find)
{
	int cnt = 0, len = 0;
	char *find_dup, *workdir;

	workdir = *(gettingenvir("PWD")) + 4;

	while (find[cnt])
	{
		if (find[cnt] == ':')
		{
			if (find[cnt + 1] == ':' || cnt == 0 || find[cnt + 1] == '\0')
				len = len + _strlen(workdir) + 1;
			else
				len++;
		}
		else
			len++;
		cnt++;
	}
	find_dup = malloc(sizeof(char) * (len + 1));
	if (!find_dup)
		return (NULL);
	find_dup[0] = '\0';
	cnt = 0;

	while (find[cnt])
	{
		if (find[cnt] == ':')
		{
			if (cnt == 0)
			{
				_strcat(find_dup, workdir);
				_strcat(find_dup, ":");
			}
			else if (find[cnt + 1] == ':' || find[cnt + 1] == '\0')
			{
				_strcat(find_dup, ":");
				_strcat(find_dup, workdir);
			}
			else
				_strcat(find_dup, ":");
		}
		else
			_strncat(find_dup, &find[cnt], 1);
		cnt++;
	}
	return (find_dup);
}

/**
 * freeinglst - used to free new_list
 * @head: beginining of the list
 * Return: 0 on success
 */
int freeinglst(new_list *head)
{
	new_list *next;

	while (head)
	{
		next = head->next;
		free(head->source);
		free(head);
		head = next;
	}
	return (0);
}

/**
 * free_al_lst - freeing alias list
 * @head: beginning of list
 * Return: 0 on success
 */
int free_al_lst(new_alias *head)
{
	new_alias *next;

	while (head)
	{
		next = head->next;
		free(head->source);
		free(head->value);
		free(head);
		head = next;
	}
	return (0);
}
