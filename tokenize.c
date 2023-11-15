#include "my_shell.h"
/**
 * tokenize - this function separates the string using a designed delimiter
 * @data: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void tokenize(data_of_program *data)
{
	char *delimiter = " \t";
	int q, counter = 2, length;

	length = str_length(data->input_line);

	if (length > 0 && data->input_line[length - 1] == '\n')
		data->input_line[length - 1] = '\0';

	for (q = 0; data->input_line[q]; q++)
	{
		for (int j = 0; delimiter[j]; j++)
		{
			if (data->input_line[q] == delimiter[j])
				counter++;
		}
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}

	q = 0;
	data->tokens[q] = str_duplicate(_strtok(data->input_line, delimiter));
	data->command_name = str_duplicate(data->tokens[0]);

	while (data->tokens[q++])
	{
		data->tokens[q] = str_duplicate(_strtok(NULL, delimiter));
	}
}
