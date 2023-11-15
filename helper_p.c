#include "my_shell.h"

/**
 * my_print - writes an array of chars to standard output
 * @str: pointer to array of chars
 * Return: total number of bytes written
 * Upon error -1, and errno is set appropriately.
 */

int my_print(char *str)
{
    printf("%s", str);
    return str_length(str);
}

/**
 * my_print_error - writes an array of chars to standard error
 * @errorcode: error code to print
 * @data: Pointer to program data
 * Return: total number of bytes written
 * On error -1, and errno is set appropriately.
 */
int my_print_error(int errorcode, data_of_program *data)
{
    char n_as_string[10] = {'\0'};

    long_to_string((long)data->exec_counter, n_as_string, 10);

    if (errorcode == 2 || errorcode == 3)
    {
        my_print_error_prefix(data);
        printf(": ");
        printf("%s", n_as_string);
        printf(": ");
        printf("%s", data->tokens[0]);
        if (errorcode == 2)
            printf(": Illegal number: ");
        else
            printf(": can't cd to ");
  
        my_print(data->tokens[1]);
        my_print("\n");
    }
    else if (errorcode == 127)
    {
        my_print_error_prefix(data);
        my_print(": ");
        my_print(n_as_string);
        my_print(": ");
        my_print(data->command_name);
        my_print(": not found\n");
    }
    else if (errorcode == 126)
    {
        my_print_error_prefix(data);
        my_print(": ");
        my_print(n_as_string);
        my_print(": ");
        my_print(data->command_name);
        my_print(": Permission denied\n");
    }

    return 0;
}

/**
 * my_print_error_prefix - writes program name, execution count, and command
 * name to standard error
 * @data: Pointer to program data
 * Return: total number of bytes written
 * On error -1, and errno is set appropriately.
 */
int my_print_error_prefix(data_of_program *data)
{
    char n_as_string[10] = {'\0'};

    long_to_string((long)data->exec_counter, n_as_string, 10);

    my_printe(data->program_name);
    my_printe(": ");
    my_printe(n_as_string);
    my_printe(": ");
    my_printe(data->tokens[0]);

    return 0;
}
