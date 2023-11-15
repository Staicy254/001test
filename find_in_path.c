#include "my_shell.h"

int my_check_file(char *full_path);

/**
 * my_find_program - find a program in the PATH
 * @data: a pointer to the program's data
 * Return: 0 if success, errcode otherwise
 */
int my_find_program(data_of_program *data)
{
	int q = 0, ret_code = 0;
	char **directories;

	if (!data->command_name)
		return (2);

	/* Check if it's a full path or an executable in the same path */
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (my_check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = my_strncat(strdup("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	directories = my_tokenize_path(data); /* Search in the PATH */

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}

	for (q = 0; directories[q]; q++)
	{
		/* Append the function_name to the path */
		directories[q] = my_strncat(directories[q], data->tokens[0]);
		ret_code = my_check_file(directories[q]);

		if (ret_code == 0 || ret_code == 126)
		{
			/* The file was found, is not a directory and has execute permissions */
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = strdup(directories[q]);
			my_free(directories);
			return (ret_code);
		}
	}

	free(data->tokens[0]);
	data->tokens[0] = NULL;
	my_frees(directories);
	return (ret_code);
}

/**
 * my_tokenize_path - tokenize the PATH into directories
 * @data: a pointer to the program's data
 * Return: array of path directories
 */
char **my_tokenize_path(data_of_program *data)
{
	int q = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;

	/* Get the PATH value */
	PATH = my_getenv("PATH", data);

	if ((PATH == NULL) || PATH[0] == '\0')
	{
		/* PATH not found */
		return (NULL);
	}

	PATH = strdup(PATH);

	/* Find the number of directories in the PATH */
	for (q = 0; PATH[q]; q++)
	{
		if (PATH[q] == ':')
			counter_directories++;
	}

	/* Reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * counter_directories);

	/* Tokenize and duplicate each token of path */
	q = 0;
	tokens[q] = strdup(strtok(PATH, ":"));
	while (tokens[q++])
	{
		tokens[q] = strdup(strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);
}

/**
 * my_check_file - checks if a file exists, if it is not a directory, and
 * if it has execution permissions.
 * @full_path: pointer to the full file name
 * Return: 0 on success, or an error code if it exists.
 */
int my_check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) || access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}

	/* If the file does not exist */
	errno = 127;
	return (127);
}
