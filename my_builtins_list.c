#include "my_shell.h"

/**
 * my_builtins_list - function that searches matches then executes a builtin.
 * @data: variable representing the struct for the program data.
 * Return: (function return type) Success, (-1) Fail
 **/ 
int my_builtins_list(data_of_program *data)
{
    if (data == NULL || data->command_name == NULL) {
        return -1;
    }

    int iterator;
    builtins options[] = {
        {"exit", builtin_exit},
        {"help", builtin_help},
        {"cd", builtin_cd},
        {"alias", builtin_alias},
        {"env", builtin_env},
        {"setenv", builtin_set_env},
        {"unsetenv", builtin_unset_env},
        {NULL, NULL}
    };

    /* structure iteration */
    for (iterator = 0; options[iterator].builtin != NULL; iterator++)
    {
        /* code executed if match is present */
        if (my_strcmp(options[iterator].builtin, data->command_name, 0))
        {
            /* if success, return the value of the function */
            return (options[iterator].function(data));
        }
    }
    /* if no match is found, return -1 */
    return (-1);
}