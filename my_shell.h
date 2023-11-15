#ifndef MY_SHELL_H
#define MY_SHELL_H

#include <stdio.h> /* for printf*/
#include <unistd.h> /* fork, execve*/
#include <stdlib.h>
#include <signal.h> /* signal management */
#include <fcntl.h> /* open files*/
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h> /* errno and perror */
#include <sys/types.h> /* type pid */

#include <sys/wait.h> /*wait*/
#include <sys/stat.h> /* use of stat function */

/************* MACROS **************/

#include "my_macros.h" /* msg help and prompt */

/************* STRUCTURES **************/

/**
 * struct info- struct for program's data
 * @program_name: name of the executable
 * @exec_counter: number of executed commands
 * @file_descriptor: file descriptor to input commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of environ
 * @input_line: pointer to input read for _getline
 * @command_name: pointer to first command input by user
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
} data_of_program;

/**
 * struct builtins - struct for the builtins
 * @builtin: name of builtin
 * @function: associated function to be called for each builtin
 */
typedef struct builtins
{
    char *builtin;
    int (*function)(data_of_program *data);
} builtins;

/************* MAIN FUNCTIONS *************/

/*========  shell.c  ========*/

/* Initialize the struct with info of the program */
void initialize_data(data_of_program *data, int argc, char *argv[], char **env);

/* Makes infinite loop that shows prompt*/
void sisifo(char *prompt, data_of_program *data);

/* Print prompt on a new line */
void handle_ctrl_c(int opr);

/*========  _getline.c  ========*/

/* Read one line of the standard input*/
int _getline(data_of_program *data);

/* split each line for the logical operators if they exist */
int check_logic_ops(char *array_commands[], int q, char array_operators[]);

/*======== expansions.c ========*/

/* Expand variables */
void expand_variables(data_of_program *data);

/* Expand aliases */
void expand_alias(data_of_program *data);

/* Append the string to the end of the buffer*/
int buffer_add(char *buffer, char *str_to_add);

/*======== str_tok.c ========*/

/* Separate string into tokens using a designated delimiter */
void tokenize(data_of_program *data);

/* Creates a pointer as a part of a string */
char *_strtok(char *line, char *delim);

/*======== execute.c ========*/

/* Execute command with entire path */
int execute(data_of_program *data);

/*======== builtins_list.c ========*/

/* If match a builtin, executes it */
int builtins_list(data_of_program *data);

/*======== find_in_path.c ========*/

/* Creates an array of path directories */
char **tokenize_path(data_of_program *data);

/* Search for a program in the path */
int find_program(data_of_program *data);

/************** HELPERS FOR MEMORY MANAGEMENT **************/

/*======== helpers_free.c ========*/

/* Frees up memory for directories */
void free_array_of_pointers(char **directories);

/* Free fields needed each loop */
void free_recurrent_data(data_of_program *data);

/* Free all fields of the data */
void free_all_data(data_of_program *data);

/************** BUILTINS **************/

/*======== builtins_more.c ========*/

/* Close shell */
int builtin_exit(data_of_program *data);

/* Change current directory */
int builtin_cd(data_of_program *data);

/* Set work directory */
int set_work_directory(data_of_program *data, char *new_dir);

/* Provide help information */
int builtin_help(data_of_program *data);

/* Set, unset, and show alias */
int builtin_alias(data_of_program *data);

/*======== builtins_env.c ========*/

/* Shows the environment where the shell runs */
int builtin_env(data_of_program *data);

/* Create or override a variable of the environment */
int builtin_set_env(data_of_program *data);

/* Delete a variable of the environment */
int builtin_unset_env(data_of_program *data);

/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/

/*======== env_management.c ========*/

/* Gets the value of an environment variable */
char *env_get_key(char *name, data_of_program *data);

/* Modify the value of the environment variable */
int env_set_key(char *key, char *value, data_of_program *data);

/* Delete a key from the environment */
int env_remove_key(char *key, data_of_program *data);

/* Prints the current environ */
void print_environ(data_of_program *data);

/************** HELPERS FOR PRINTING **************/

/*======== helpers_print.c ========*/

/* Prints a string in the standard output */
int _print(char *string);

/* Prints a string in the standard error */
int _printe(char *string);

/* Prints a string in the standard error */
int _print_error(int errorcode, data_of_program *data);

/************** HELPERS FOR STRINGS MANAGEMENT **************/

/*======== helpers_string.c ========*/

/* Counts the number of characters in a string */
int str_length(char *string);

/* Duplicates a string */
char *str_duplicate(char *string);

/* Compares 2 strings */
int str_compare(char *string1, char *string2, int number);

/* Concatenates 2 strings */
char *str_concat(char *string1, char *string2);

/* Reverses a string */
void str_reverse(char *string);

/*======== helpers_numbers.c ========*/

/* Cast from int to string */
void long_to_string(long number, char *string, int base);

/* Parse the string into a number */
int _atoi(char *k);

/* Count the coincidences of a character in a string */
int count_characters(char *string, char *character);

/*======== alias_management.c ========*/

/* Print the list of aliases */
int print_alias(data_of_program *data, char *alias);

/* Get the alias name */
char *get_alias(data_of_program *data, char *alias);

/* Set the alias name */
int set_alias(char *alias_string, data_of_program *data);

#endif /* MY_SHELL_H */
