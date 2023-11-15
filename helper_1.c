#include "my_shell.h"

/**
 * my_free_recurrent_data - free fields needed for each loop
 * @data: struct of program's data
 * Return: Nothing
 */
void my_free_recurrent_data(data_of_program *data)
{
    if (data->tokens)
        my_free_array_of_pointers(data->tokens);
    if (data->input_line)
        free(data->input_line);
    if (data->command_name)
        free(data->command_name);

    data->input_line = NULL;
    data->command_name = NULL;
    data->tokens = NULL;
}

/**
 * my_free_all_data - free field of the data
 * @data: struct of program's data
 * Return: Nothing
 */
void my_free_all_data(data_of_program *data)
{
    if (data->file_descriptor != 0)
    {
        if (close(data->file_descriptor))
            perror(data->program_name);
    }
    my_free_recurrent_data(data);
    my_free_array_of_pointers(data->env);
    my_free_array_of_pointers(data->alias_list);
}

/**
 * my_free_array_of_pointers - frees each pointer of an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: nothing
 */
void my_free_array_of_pointers(char **array)
{
    int q;

    if (array != NULL)
    {
        for (q = 0; array[q]; q++)
            free(array[q]);

        free(array);
        array = NULL;
    }
}
