#include "my_shell.h"

/**
 * my_strlen - outputs the length of string
 * @str: pointer to string.
 * Return: length of string.
 */
size_t my_strlen(char *str)
{
    size_t length = 0;

    if (str == NULL)
        return 0;

    while (str[length++] != '\0')
    {
    }
    return --length;
}
/**
 * my_strdup - copies a string
 * @str: String to copy
 * Return: pointer to the array
 */
char *my_strdup(char *str)
{
    char *result;
    int length, q;

    if (str == NULL)
        return NULL;

    length = my_strlen(str) + 1;

    result = malloc(sizeof(char) * length);

    if (result == NULL)
    {
        errno = ENOMEM;
        perror("Error");
        return NULL;
    }

    for (q = 0; q < length; q++)
    {
        result[q] = str[q];
    }

    return result;
}

/**
 * my_strcmp - does comparison of 2 strings
 * @str1: String 1, or shorter
 * @str2: String 2, or longer
 * @number: total no. of char for comparison, 0 if infinite
 * Return: 1 if strings are equals, 0 if different
 */
int my_strcmp(char *str1, char *str2, int number)
{
    int iterator;

    if (str1 == NULL && str2 == NULL)
        return 1;

    if (str1 == NULL || str2 == NULL)
        return 0;

    if (number == 0) /* infinite length */
    {
        if (my_strlen(str1) != my_strlen(str2))
            return 0;
        for (iterator = 0; str1[iterator]; iterator++)
        {
            if (str1[iterator] != str2[iterator])
                return 0;
        }
        return 1;
    }
    else /* if there is a number of chars to be compared */
    {
        for (iterator = 0; iterator < number; iterator++)
        {
            if (str1[iterator] != str2[iterator])
                return 0;
        }
        return 1;
    }
}

/**
 * my_strcat - concatenates 2 strings.
 * @str1: String to concatenate
 * @str2: String to concatenate
 * Return: pointer to the array
 */
char *my_strcat(char *str1, char *str2)
{
    char *result;
    int length1 = 0, length2 = 0;

    if (str1 == NULL)
        str1 = "";
    length1 = my_strlen(str1);

    if (str2 == NULL)
        str2 = "";
    length2 = my_strlen(str2);

    result = malloc(sizeof(char) * (length1 + length2 + 1));
    if (result == NULL)
    {
        errno = ENOMEM;
        perror("Error");
        return NULL;
    }

    /* duplicate of str1 */
    for (length1 = 0; str1[length1] != '\0'; length1++)
        result[length1] = str1[length1];
    free(str1);

    /* duplicate of str2 */
    for (length2 = 0; str2[length2] != '\0'; length2++)
    {
        result[length1] = str2[length2];
        length1++;
    }

    result[length1] = '\0';
    return result;
}

/**
 * my_strreverse - reverse of string.
 * @str: pointer to string.
 * Return: void.
 */
void my_strreverse(char *str)
{
    int q = 0, length = my_strlen(str) - 1;
    char hold;

    while (q < length)
    {
        hold = str[q];
        str[q++] = str[length];
        str[length--] = hold;
    }
}
