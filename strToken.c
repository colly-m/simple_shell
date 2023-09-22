#include "shell.h"
/**
 * _strtok - function to separates the string with delimiters
 * @line: pointer to the array received in getline.
 * @delim: pointer to char marked off string in parts.
 * Return: A pointer to the token
*/
char *_strtok(char *line, char *delim)
{
	int i;
	static char *str;
	char *cpstr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*str == delim[i])
			break;
		}
		if (delim[i] == '\0')
			break;
	}
	cpstr = str;
	if (*cpstr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*str == delim[i])
			{
				*str = '\0';
				str++;
				return (cpstr);
			}
		}
	}
	return (cpstr);
}
