#include "my_shell.h"

/**
 * my_print_alias - function that manipulates (add, remove or show) alias.
 * @data: variable representing the struct for our program data.
 * @alias: represents the name of the alias to be printed.
 * Return: (zero) Success, or (non-zero value present in the arguments).
 */
int my_print_alias(data_of_program *data, char *alias)
{
    int q, r, alias_length;
    char buffer[250] = {'\0'};

    if (data->alias_list)
    {
        alias_length = my_str_length(alias);
        for (q = 0; data->alias_list[q]; q++)
        {
            if (!alias || (my_str_compare(data->alias_list[q], alias, alias_length)
                && data->alias_list[q][alias_length] == '='))
            {
                for (r = 0; data->alias_list[q][r]; r++)
                {
                    buffer[r] = data->alias_list[q][r];
                    if (data->alias_list[q][r] == '=')
                        break;
                }
                buffer[r + 1] = '\0';
                buffer_add(buffer, "'");
                buffer_add(buffer, data->alias_list[q] + r + 1);
                buffer_add(buffer, "'\n");
                _print(buffer);
            }
        }
    }

    return (0);
}

/**
 * my_get_alias - function that manipulates (add, remove or show) alias.
 * @data: variable representing the struct for our program data.
 * @name: the requested alias' name.
 * Return: (zero) Success, or (non-zero value present in the arguments).
 */
char *my_get_alias(data_of_program *data, char *name)
{
    int q, alias_length;

    /* argument validation */
    if (name == NULL || data->alias_list == NULL)
        return (NULL);

    alias_length = my_str_length(name);

    for (q = 0; data->alias_list[q]; q++)
    {
        /* checking for coincidence in varname; through iteration of the environ */
        if (my_str_compare(name, data->alias_list[q], alias_length) &&
            data->alias_list[q][alias_length] == '=')
        {
            /* returns the key NAME= value when present */
            return (data->alias_list[q] + alias_length + 1);
        }
    }
    /* return== NULL if absent */
    return (NULL);
}

/**
 * my_set_alias - function that manipulates (add, or override) alias.
 * @alias_string: set the alias in the form (name='value').
 * @data: variable representing the struct of our program data.
 * Return: (zero) Success, or (non-zero value present in the arguments)
 */
int my_set_alias(char *alias_string, data_of_program *data)
{
    int q, r;
    char buffer[250] = {'0'}, *temp = NULL;

    /* argument validation */
    if (alias_string == NULL ||  data->alias_list == NULL)
        return (1);
    
    /* finding char by iterating through alias */
    for (q = 0; alias_string[q]; q++)
        if (alias_string[q] != '=')
            buffer[q] = alias_string[q];
        else
        {
            /* finding alias value in other aliases */
            temp = my_get_alias(data, alias_string + q + 1);
            break;
        }

    /* checks for varname coincidence by iterating through the alias list */
    for (r = 0; data->alias_list[r]; r++)
        if (my_str_compare(buffer, data->alias_list[r], q) &&
            data->alias_list[r][q] == '=')
        {
            /* freeing alias memory if already allocated */
            free(data->alias_list[r]);
            break;
        }

    /* adding alias */
    if (temp)
    {
        /* if added alias exists */
        buffer_add(buffer, "=");
        buffer_add(buffer, temp);
        data->alias_list[r] = my_str_duplicate(buffer);
    }
    else
    {
        /* if added alias does not exist */
        data->alias_list[r] = my_str_duplicate(alias_string);
    }
    return (0);
}
