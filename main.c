#include "my_shell.h"

/**
 * main - initialize the variables of the program
 * @argc: no. of values received from the command line
 * @argv: values received from the command line
 * @env: no. of values received from the command line
 * Return: zero upon success.
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	initialize_data(data, argc, argv, env);
	set_signal_handlers();
	set_prompt(argc, argv, &prompt);

	errno = 0;
	run_shell(prompt, data);
	return (0);
}

void set_signal_handlers()
{
	signal(SIGINT, handle_ctrl_c);
}

void set_prompt(int argc, char *argv[], char **prompt)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		*prompt = MY_PROMPT_MSG;
	}
}

void run_shell(char *prompt, data_of_program *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			free_recurrent_data(data);
		}
	}
}

/**
 * handle_ctrl_c - print prompt on a new line
 * when the signal SIGINT (ctrl + c) is sent to the program
 * @UNUSED: option of prototype
 */
void handle_ctrl_c(int opr)
{
	_print("\n");
	_print(MY_PROMPT_MSG);
}

/**
 * initialize_data - initialize the struct with the info of the program
 * @data: pointer of structure of data
 * @argv: array of arguments parsed to program for execution
 * @env: environ parsed to program for execution
 * @argc: no. of values received from command line
 */
void initialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int q = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	/* define the file descriptor to be readed*/
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[q]; q++)
		{
			data->env[q] = str_duplicate(env[q]);
		}
	}
	data->env[q] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (q = 0; q < 20; q++)
	{
		data->alias_list[q] = NULL;
	}
}
/**
 * sisifo - an infinite loop that shows prompt
 * @prompt: prompt to print
 * @data: an infinite loop that shows prompt
 */
void sisifo(char *prompt, data_of_program *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno); /* if EOF is the first Char of string, exit*/
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{ /* if  text is given to prompt, execute */
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			free_recurrent_data(data);
		}
	}
}
