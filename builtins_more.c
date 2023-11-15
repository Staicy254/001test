#include "my_shell.h"

/**
 * my_builtin_exit - function for exit of a program.
 * @data: variable representing the struct for the program data.
 * Return: (0) if success, (non-zero value) if failed.
 */
int my_builtin_exit(data_of_program *data)
{
    int q;

    if (data->tokens[1] != NULL)
    {/* when an argument for exit is found, check if it is a number */
        for (q = 0; data->tokens[1][q]; q++)
            if ((data->tokens[1][q] < '0' || data->tokens[1][q] > '9')
                && data->tokens[1][q] != '+')
            {/* When it is not a number: */
                errno = 2;
                return (2);
            }
        errno = _my_atoi(data->tokens[1]);
    }
    free_all_data(data);
    exit(errno);
}

/**
 * my_builtin_cd - A function that changes the present working directory.
 * @data: variable representing the struct for the program data.
 * Return: (0) if success, (non-zero value) Fail.
 */
int my_builtin_cd(data_of_program *data)
{
    char *dir_home = my_getenv("HOME", data), *dir_old = NULL;
    char old_dir[128] = {0};
    int error_code = 0;

    if (data->tokens[1])
    {
        if (my_strcmp(data->tokens[1], "-", 0))
        {
            dir_old = my_getenv("OLDPWD", data);
            if (dir_old)
            {
                error_code = my_set_work_directory(data, dir_old);
                if (error_code != 0)
                {
                    // Handle error here
                    perror("chdir");
                    return error_code;
                }
            }
            _print(my_getenv("PWD", data));
            _print("\n");

            return (error_code);
        }
        else
        {
            return (my_set_work_directory(data, data->tokens[1]));
        }
    }
    else
    {
        if (!dir_home)
            dir_home = getcwd(old_dir, 128);

        return (my_set_work_directory(data, dir_home));
    }
    return (0);
}
/**
 * my_set_work_directory - function that sets the working directory.
 * @data: variable representing the struct for the program data.
 * @new_dir: variable representing the path to be set as a working directory.
 * Return: (0) if success, or (non-zero value provided in arguments).
 */
int my_set_work_directory(data_of_program *data, char *new_dir)
{
    char old_dir[128] = {0};
    int err_code = 0;

    getcwd(old_dir, 128);

    if (!my_strcmp(old_dir, new_dir, 0))
    {
        err_code = chdir(new_dir);
        if (err_code == -1)
        {
            errno = 2;
            return (3);
        }
        my_getenv("PWD", new_dir, data);
    }
    my_getenv("OLDPWD", old_dir, data);
    return (0);
}

/**
 * my_builtin_help - A function that shows the environment where our shell is run.
 * @data: variable representing the struct for the program data.
 * Return: (0) if success, or (non-zero value passed in the argument).
 */
int my_builtin_help(data_of_program *data)
{
    int q, length = 0;
    char *messages[6] = {NULL};

   /* messages[0] = MY_HELP_MSG;*/

    /* argument validation */
    if (data->tokens[1] == NULL)
    {
        _print(messages[0] + 6);
        return (1);
    }
    if (data->tokens[2] != NULL)
    {
        errno = E2BIG;
        perror(data->command_name);
        return (5);
    }
    messages[1] = MY_HELP_EXIT_MSG;
    messages[2] = MY_HELP_ENV_MSG;
    /*messages[3] = MY_HELP_SETENV_MSG;*/
    messages[4] = MY_HELP_UNSETENV_MSG;
    /*messages[5] = MY_HELP_CD_MSG;*/

    for (q = 0; messages[q]; q++)
    {
        length = my_strlen(data->tokens[1]);
        if (my_strcmp(data->tokens[1], messages[q], length))
        {
            _print(messages[q] + length + 1);
            return (1);
        }
    }
    /* when no match present, print error and then return -1 */
    errno = EINVAL;
    perror(data->command_name);
    return (0);
}

/**
 * my_builtin_alias - Function that manipulates aliases by (add, remove or show).
 * @data: variable representing the struct for the program data.
 * Return: (0) success, or (non-zero value present as arguments).
 */
int my_builtin_alias(data_of_program *data)
{
    int q = 0;

    /* When no argument present; print all env var */
    if (data->tokens[1] == NULL)
        return (my_print_alias(data, NULL));

    while (data->tokens[++q])
    {/* When argument present; set or print env vars */
        if (my_count_characters(data->tokens[q], "="))
            my_set_alias(data->tokens[q], data);
        else
            my_print_alias(data, data->tokens[q]);
    }

    return (0);
}

