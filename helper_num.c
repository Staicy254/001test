#include "my_shell.h"

/**
 * my_long_to_string - converts number to string.
 * @number: number to be converted to string.
 * @string: buffer to save number as string.
 * @base: base for number conversion
 *
 * Return: Nothing.
 */
void my_long_to_string(long number, char *string, int base, int size)
{
    int index = 0, inNegative = 0;
    long quotient = number;
    char letters[] = {"0123456789abcdef"};

    if (quotient == 0)
        string[index++] = '0';

    if (string[0] == '-')
        inNegative = 1;

    while (quotient)
    {
        if (quotient < 0)
            string[index++] = letters[-(quotient % base)];
        else
            string[index++] = letters[quotient % base];
        quotient /= base;

        if (index >= size - 1) // Check if buffer is full
            break;
    }

    if (inNegative)
        string[index++] = '-';

    string[index] = '\0';
    str_reverse(string);
}
/**
 * my_atoi - convert str to int.
 *
 * @str: pointer to string origin.
 * Return: int of string or 0.
 */
int my_atoi(char *str)
{
    int sign = 1;
    unsigned int number = 0;

    while (!('0' <= *str && *str <= '9') && *str != '\0')
    {
        if (*str == '-')
            sign *= -1;
        if (*str == '+')
            sign *= +1;
        str++;
    }

    while ('0' <= *str && *str <= '9' && *str != '\0')
    {
        number = (number * 10) + (*str - '0');
        str++;
    }

    return (number * sign);
}

/**
 * my_count_characters - count instances of chars in string.
 *
 * @str: pointer to str origin.
 * @character: string with the chars to be counted
 * Return: int of string or 0.
 */
int my_count_characters(char *str, char *character)
{
    int q = 0, counter = 0;

    for (; str[q]; q++)
    {
        if (str[q] == character[0])
            counter++;
    }

    return counter;
}
