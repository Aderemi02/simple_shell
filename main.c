#include "shell.h"
/**
 * main - the entry to the program
 * @ac: the number of argument
 * @av: list of arg or prog
 * Return: last executed command
 */
int main(int ac, char *av[])
{
	char *prompt = "cisfun$ ", *ln = "\n";
	int rep = 0, reppin, *addrep = &reppin;

	global_alias = NULL, global_history = 1, source = av[0];
	signal(SIGINT, signal_hand);
	*addrep = 0;
	environ = copyingenvir();
	if (!environ)
		exit(-20);
	if (ac != 1)
	{
		rep = file_comm(av[1], addrep);
		freeingenvir();
		free_al_lst(global_alias);
		return (*addrep);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (rep != -2 && rep != -3)
			rep = handle_arguments(addrep);
		freeingenvir();
		free_al_lst(global_alias);
		return (*addrep);
	}
	while (1)
	{
		write(STDOUT_FILENO, prompt, 8);
		rep = handle_arguments(addrep);
		if (rep == -2 || rep == -3)
		{
			if (rep == -2)
				write(STDOUT_FILENO, ln, 1);
			freeingenvir();
			free_al_lst(global_alias);
			exit(*addrep);
		}
	}
	freeingenvir();
	free_al_lst(global_alias);
	return (*addrep);
}

/**
 * signal_hand - handles the signal to print new prompt
 * @input_signal: signal
 */
void signal_hand(int input_signal)
{
	char *anprmpt = "\ncisfun$ ";

	(void)input_signal;
	signal(SIGINT, signal_hand);
	write(STDIN_FILENO, anprmpt, 9);
}
