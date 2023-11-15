#include "my_shell.h"

/**
 * my_execute - function that executes its entire path variables.
 * @data: variable representing a pointer to the program data.
 * Return: (0) success, or (-1) Fail.
 */
int my_execute(data_of_program *data)
{
    int retval = 0, status;
    pid_t pid;

    /* looking for programs builtins */
    retval = my_builtins_list(data);
    if (retval != -1)/* if builtins has the program; */
        return (retval);

    /* checking for the file system of the*/
    retval = my_find_program(data);
    if (retval)
    {/* when not found;*/
        return (retval);
    }
    else
    {/* When found;*/
        pid = fork(); /* create a new child process */
        if (pid == -1)
        { /* when fork fails;*/
            perror(data->command_name);
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {/* the child process that executes the program */
            retval = execve(data->tokens[0], data->tokens, data->env);
            if (retval == -1) /* if error when execve */
                perror(data->command_name), exit(EXIT_FAILURE);
        }
        else
        {/* parent process that waits and checks the exit status of the child */
            wait(&status);
            if (WIFEXITED(status))
                errno = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                errno = 128 + WTERMSIG(status);
        }
    }
    return (0);
}
