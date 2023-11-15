#include "my_shell.h"
/**
 * _strtok - separates strings with delimiters
 * @line: pointer to array we get in getline.
 * @delim: characters we mark off string in parts.
 * Return: Pointer to created token
 */
char *_strtok(char *line, char *delim)
{
	static char *str;
	char *copystr;
	int r;

	if (line != NULL)
		str = line;

	for (; *str != '\0'; str++)
	{
		for (r = 0; delim[r] != '\0'; r++)
		{
			if (*str == delim[r])
				break;
		}
		if (delim[r] == '\0')
			break;
	}

	copystr = str;

	if (*copystr == '\0')
		return (NULL);

	for (; *str != '\0'; str++)
	{
		for (r = 0; delim[r] != '\0'; r++)
		{
			if (*str == delim[r])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}

	return (copystr);
}
