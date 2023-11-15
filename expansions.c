#include "my_shell.h"

/**
 * my_expand_variables - function that expands variables.
 * @data: a variable representing a pointer to a struct of the program's data.
 * Return: none, sets errno.
 */
void my_expand_variables(data_of_program *data)
{
    int q, r;
    char line[MY_BUFFER_SIZE] = {0}, expansion[MY_BUFFER_SIZE] = {'\0'}, *temp;

    if (data->input_line == NULL)
        return;
    my_buffer_add(line, data->input_line);
    for (q = 0; line[q]; q++)
        if (line[q] == '#')
            line[q--] = '\0';
        else if (line[q] == '$' && line[q + 1] == '?')
        {
            line[q] = '\0';
            my_long_to_string(errno, expansion, 10);
            my_buffer_add(line, expansion);
            my_buffer_add(line, data->input_line + q + 2);
        }
        else if (line[q] == '$' && line[q + 1] == '$')
        {
            line[q] = '\0';
            my_long_to_string(getpid(), expansion, 10);
            my_buffer_add(line, expansion);
            my_buffer_add(line, data->input_line + q + 2);
        }
        else if (line[q] == '$' && (line[q + 1] == ' ' || line[q + 1] == '\0'))
            continue;
        else if (line[q] == '$')
        {
            for (r = 1; line[q + r] && line[q + r] != ' '; r++)
                expansion[r - 1] = line[q + r];
            temp = my_env_get_key(expansion, data);
            line[q] = '\0', expansion[0] = '\0';
            my_buffer_add(expansion, line + q + r);
            temp ? my_buffer_add(line, temp) : 1;
            my_buffer_add(line, expansion);
        }
    if (!my_str_compare(data->input_line, line, 0))
    {
        free(data->input_line);
        data->input_line = my_str_duplicate(line);
    }
}

/**
 * my_expand_alias - function that expands aliases.
 * @data: a variable representing a pointer to a struct of the program's data.
 * Return: none, sets errno.
 */
void my_expand_alias(data_of_program *data)
{
    int q, r, was_expanded = 0;
    char line[MY_BUFFER_SIZE] = {0}, expansion[MY_BUFFER_SIZE] = {'\0'}, *temp;

    if (data->input_line == NULL)
        return;

    my_buffer_add(line, data->input_line);

    for (q = 0; line[q]; q++)
    {
        for (r = 0; line[q + r] && line[q + r] != ' '; r++)
            expansion[r] = line[q + r];
        expansion[r] = '\0';

        temp = my_get_alias(data, expansion);
        if (temp)
        {
            expansion[0] = '\0';
            my_buffer_add(expansion, line + q + r);
            line[q] = '\0';
            my_buffer_add(line, temp);
            line[my_str_length(line)] = '\0';
            my_buffer_add(line, expansion);
            was_expanded = 1;
        }
        break;
    }
    if (was_expanded)
    {
        free(data->input_line);
        data->input_line = my_str_duplicate(line);
    }
}

/**
 * my_buffer_add - function that appends a string at the end of the buffer.
 * @buffer: a variable representing the buffer to be filled.
 * @str_to_add: a variable representing the string to be copied into the buffer.
 * Return: none, sets errno.
 */
int my_buffer_add(char *buffer, char *str_to_add)
{
    int length, q;

    length = my_str_length(buffer);
    for (q = 0; str_to_add[q]; q++)
    {
        buffer[length + q] = str_to_add[q];
    }
    buffer[length + q] = '\0';
    return (length + q);
}
