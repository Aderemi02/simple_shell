#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>



/**
 * struct builtin - defining builtin
 * @source: source of builtin
 * @func: function pointer to the builtin command passed
 */
typedef struct builtin
{
	char *source;
	int (*func)(char **args, char **beginning);
} new_builtin;

/**
 * struct alias - defining alias
 * @source: source of alias
 * @value: value of alias
 * @next: another alias
 */
typedef struct alias
{
	char *source;
	char *value;
	struct alias *next;
} new_alias;

/**
 * struct lists - defining new list
 * @source: new list path
 * @next: next list path
 */
typedef struct lists
{
	char *source;
	struct lists *next;
} new_list;

extern char **environ;
char *source;
int global_history;
new_alias *global_alias;

#define EOF_CODE -2
#define EXIT_CODE -3

/************String Functions***************/
char *_strncat(char *dest, char *src, int n);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
int _strncmp(char *s1, char *s2, size_t n);
char *_strchr(char *s, char c);
char *_strcpy(char *dest, char *src);
unsigned int _strspn(char *s, char *accept);
char **_strtok(char *readline, char *delimit);


/*************Main Helper Functions***************/
int main(int ac, char *av[]);
void *reallocation(void *p, unsigned int former, unsigned int nw);
ssize_t _getline(char **ptr, size_t *num, FILE *stream);
void assigning(char **ptr, size_t *num, char *buff, size_t pass);
new_alias *add_end_alias(new_alias **head, char *source, char *value);
new_list *add_end_node(new_list **head, char *source);
int exec(char **a1, char **beginning);
char *fill_direction(char *find);
new_list *get_direction(char *find);
char *loc(char *comm);
void signal_hand(int input_signal);


/********Tokenizing Functions*********/
int counting_token(char *s1, char *delimit);
int token_length(char *s1, char *delimit);


/********Free Pointer Functions*********/
int free_al_lst(new_alias *head);
int freeinglst(new_list *head);

/**********Processing File Functions***********/
int file_comm(char *file, int *addrep);
int unable(char *file);

/********Alias Builtin Functions*************/
int builtin_alias(char **args, char __attribute__((__unused__)) **beginning);
void set_alias(char *source, char *value);
char **replace_alias(char **args);
void print_alias(new_alias *alias);

/********Environ Builtin Functions*************/
int builtin_env(char **args, char __attribute__((__unused__)) **beginning);
int builtin_setenv(char **args, char __attribute__((__unused__)) **beginning);
int builtin_unsetenv(char **args, char __attribute__((__unused__)) **beginning);

/********Other Builtin Functions*************/
int (*get_builtin_func(char *command))(char **args, char **beginning);
int builtin_exit(char **args, char **beginning);
int builtin_cd(char **args, char __attribute__((__unused__)) **beginning);

/********Helper Functions*************/
void free_arguments(char **args, char **beginning);
char *get_pid(void);
char *get_environ_value(char *source, int len);
void replace_env(char **args, int *last_command);

void split_line(char **line, ssize_t read);
ssize_t get_line_length(char *line);
void check_operator(char *line, ssize_t *new_length);


char *get_arguments(char *line, int *last_command);
int check_arguments(char **args);
int call_arguments(char **args, char **beginning, int *last_command);
int run_arguments(char **args, char **beginning, int *last_command);
int handle_arguments(int *last_command);


/********Environ Functions*************/
void freeingenvir(void);
char **gettingenvir(char *identity);
char **copyingenvir(void);

/********Error Functions*************/
char *error_env(char **args);
char *error_alias(char **args);
char *error_cd(char **args);
char *error_exit(char **args);
char *error_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);
int create_error(char **args, int error_code);
int num_len(int num);
char *_itoa(int num);

#endif
