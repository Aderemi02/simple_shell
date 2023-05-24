#include "shell.h"
/**
 * add_end_alias - adding a nod to the alias list
 * @head: the beginning of the alias list
 * @source: alias to be created
 * @value: value of the alias
 * Return: new node on success
 */
new_alias *add_end_alias(new_alias **head, char *source, char *value)
{
	new_alias *Nnode, *Lnode;

	Nnode = malloc(sizeof(new_alias));

	if (!Nnode)
		return (NULL);

	Nnode->next = NULL;
	Nnode->source = malloc(sizeof(char) * (_strlen(source) + 1));

	if (!Nnode->source)
	{
		free(Nnode);
		return (NULL);
	}
	Nnode->value = value;
	_strcpy(Nnode->source, source);

	if (*head)
	{
		Lnode = *head;
		while (Lnode->next != NULL)
			Lnode = Lnode->next;
		Lnode->next = Nnode;
	}
	else
		*head = Nnode;
	return (Nnode);
}

/**
 * add_end_node - adds a node to the end
 * @head: pointer to the beginning of node
 * @source: the directory
 * Return: new node on success
 */
new_list *add_end_node(new_list **head, char *source)
{
	new_list *Nnode, *Lnode;

	Nnode = malloc(sizeof(new_alias));

	if (!Nnode)
		return (NULL);

	Nnode->next = NULL;
	Nnode->source = source;

	if (*head)
	{
		Lnode = *head;
		while (Lnode->next != NULL)
			Lnode = Lnode->next;
		Lnode->next = Nnode;
	}
	else
		*head = Nnode;
	return (Nnode);
}

/**
 *freeingenvir - freeing the environment
 */
void freeingenvir(void)
{
	int ind = 0;

	while (environ[ind])
	{
		free(environ[ind]);
		ind++;
	}
	free(environ);
}

/**
 * gettingenvir - getting the envir variable
 * @identity: environment variable to get
 * Return: pointer to envir variable
 */
char **gettingenvir(char *identity)
{
	int ind = 0, length;

	length = _strlen(identity);

	while (environ[ind])
	{
		if (_strncmp(identity, environ[ind], length) == 0)
			return (&environ[ind]);
		ind++;
	}
	return (NULL);
}

/**
 * copyingenvir - copying environment
 * Return: new environment on success
 */
char **copyingenvir(void)
{
	int ind = 0;
	char **Nenvir;
	size_t len = 0;

	while (environ[len])
	{
		len++;
	}

	Nenvir = malloc(sizeof(char *) * (len + 1));
	if (!Nenvir)
		return (NULL);

	while (environ[ind])
	{
		Nenvir[ind] = malloc(_strlen(environ[ind]) + 1);
		if (!Nenvir[ind])
		{
			for (ind--; ind >= 0; ind--)
				free(Nenvir[ind]);
			free(Nenvir);
			return (NULL);
		}
		_strcpy(Nenvir[ind], environ[ind]);
		ind++;
	}
	Nenvir[ind] = NULL;
	return (Nenvir);
}
