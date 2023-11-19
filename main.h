#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>  /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h>     /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h>  /* for wait */
#include <sys/stat.h>  /* for use of stat function */
#include <signal.h>    /* for signal management */
#include <fcntl.h>     /* for open files*/

/************* MACROS **************/

#include "macros.h" /* for msg help and prompt */

/************* STRUCTURES **************/

/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted commands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
    char *program_name;
    char *input_line;
    char *command_name;
    int exec_counter;
    int file_descriptor;
    char **tokens;
    char **env;
    char **alias_list;
} var_data;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
    char *builtin;
    int (*function)(var_data *data);
} builtins;

/************* MAIN FUNCTIONS *************/

/*========  shell.c  ========*/

/* Initialize the struct with the info of the program */
void initialize_data(var_data *data, int arc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void rollover(char *prompt, var_data *data);

/* Print the prompt in a new line */
void handle_ctrl_c(int opr UNUSED);

/*========  _getline.c  ========*/

/* Read one line of the standar input*/
int _getline(var_data *data);

/* split the each line for the logical operators if it exist */
int check_logic_ops(char *array_commands[], int i, char array_operators[]);

/*======== expansions.c ========*/

/* expand variables */
void expand_variables(var_data *data);

/* expand aliases */
void expand_alias(var_data *data);

/* append the string to the end of the buffer*/
int buffer_add(char *buffer, char *str_to_add);

/*======== str_tok.c ========*/

/* Separate the string in tokens using a designed delimiter */
void tokenize(var_data *data);

/* Creates a pointer to a part of a string */
char *_strtok(char *line, char *delim);

/*======== execute.c ========*/

/* Execute a command with its entire path */
int execute(var_data *data);

/*======== builtins_list.c ========*/

/* If match a builtin, executes it */
int builtins_list(var_data *data);

/*======== find_in_path.c ========*/

/* Creates an array of the path directories */
char **tokenize_path(var_data *data);

/* Search for program in path */
int find_program(var_data *data);

/************** HELPERS FOR MEMORY MANAGEMENT **************/

/*======== helpers_free.c ========*/

/* Frees the memory for directories */
void free_array_of_pointers(char **directories);

/* Free the fields needed each loop */
void free_recurrent_data(var_data *data);

/* Free all field of the data */
void free_all_data(var_data *data);

/************** BUILTINS **************/

/*======== builtins_more.c ========*/

/* Close the shell */
int builtin_exit(var_data *data);

/* Change the current directory */
int builtin_cd(var_data *data);

/* set the work directory */
int set_work_directory(var_data *data, char *new_dir);

/* show help information */
int builtin_help(var_data *data);

/* set, unset and show alias */
int builtin_alias(var_data *data);

/*======== builtins_env.c ========*/

/* Shows the environment where the shell runs */
int builtin_env(var_data *data);

/* create or override a variable of environment */
int builtin_set_env(var_data *data);

/* delete a variable of environment */
int builtin_unset_env(var_data *data);

/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/

/*======== env_management.c ========*/

/* Gets the value of an environment variable */
char *env_get_key(char *name, var_data *data);

/* Overwrite the value of the environment variable */
int env_set_key(char *key, char *value, var_data *data);

/* Remove a key from the environment */
int env_remove_key(char *key, var_data *data);

/* prints the current environ */
void print_environ(var_data *data);

/************** HELPERS FOR PRINTING **************/

/*======== helpers_print.c ========*/

/* Prints a string in the standar output */
int _print(char *string);

/* Prints a string in the standar error */
int _printe(char *string);

/* Prints a string in the standar error */
int _print_error(int errorcode, var_data *data);

/************** HELPERS FOR STRINGS MANAGEMENT **************/

/*======== helpers_string.c ========*/

/* Counts the number of characters of a string */
int str_length(char *string);

/* Duplicates an string */
char *str_duplicate(char *string);

/* Compares two strings */
int str_compare(char *string1, char *string2, int number);

/* Concatenates two strings */
char *str_concat(char *string1, char *string2);

/* Reverse a string */
void str_reverse(char *string);

/*======== helpers_numbers.c ========*/

/* Cast from int to string */
void long_to_string(long number, char *string, int base);

/* convert an string in to a number */
int _atoi(char *s);

/* count the coincidences of character in string */
int count_characters(char *string, char *character);

/*======== alias_management.c ========*/

/* print the list of alias */
int print_alias(var_data *data, char *alias);

/* get the alias name */
char *get_alias(var_data *data, char *alias);

/* set the alias name */
int set_alias(char *alias_string, var_data *data);

#endif /* SHELL_H */


