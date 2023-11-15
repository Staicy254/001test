#include "my_shell.h"

/**
* my_getline - takes 1 line input from prompt.
* @data: variable rep structure of the program data.
*
* Return: (reads the count bytes)Success.
*/
int my_getline(data_of_program *data)
{
    char buff[MY_BUFFER_SIZE] = {'\0'};
    static char *array_commands[10] = {NULL};
    static char array_operators[10] = {'\0'};
    ssize_t bytes_read, q = 0;

    /* checks for additional commands in the array. */
    /* check for all logical operators. */
    if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
        (array_operators[0] == '|' && errno == 0))
    {
        /*if memory allocated to array exist: free it. */
        for (q = 0; array_commands[q]; q++)
        {
            free(array_commands[q]);
            array_commands[q] = NULL;
        }

        /* reading into buffer from the file descriptor */
        bytes_read = read(data->file_descriptor, &buff, MY_BUFFER_SIZE - 1);
        if (bytes_read == 0)
            return (-1);

        /* for (\n or ;) character, split lines */
        q = 0;
        do {
            array_commands[q] = strdup(my_strtok(q ? NULL : buff, "\n;"));
            /*checks the presence of && and || operators*/
            /*and splits them*/
            q = check_logic_ops(array_commands, q, array_operators);
        } while (array_commands[q++]);
    }

    /*get the next command*/
    /*delete it from the array*/
    data->input_line = array_commands[0];
    for (q = 0; array_commands[q]; q++)
    {
        array_commands[q] = array_commands[q + 1];
        array_operators[q] = array_operators[q + 1];
    }

    return (my_strlen(data->input_line));
}

/**
* check_logic_ops - function that checks for && and || operators
* and split them.
* @array_commands: variable representing the array of passed commands.
* @q: array command index to be checked.
* @array_operators: variable representing the array
* of logical operators for each of the previous command.
*
* Return: last command index.
*/
int check_logic_ops(char *array_commands[], int q, char array_operators[])
{
    char *temp = NULL;
    int r;

    /* checking (&) character in the command line*/
    for (r = 0; array_commands[q] != NULL && array_commands[q][r]; r++)
    {
        if (array_commands[q][r] == '&' && array_commands[q][r + 1] == '&')
        {
            /* if && character is found; splitting line */
            temp = array_commands[q];
            array_commands[q][r] = '\0';
            array_commands[q] = strdup(array_commands[r]);
            array_commands[q + 1] = strdup(temp + r + 2);
            q++;
            array_operators[q] = '&';
            free(temp);
            r = 0;
        }
        if (array_commands[q][r] == '|' && array_commands[q][r + 1] == '|')
        {
            /*if || character is found; split line */
            temp = array_commands[q];
            array_commands[q][r] = '\0';
            array_commands[q] = strdup(array_commands[q]);
            array_commands[q + 1] = strdup(temp + r + 2);
            q++;
            array_operators[q] = '|';
            free(temp);
            r = 0;
        }
    }
    return (q);
}
