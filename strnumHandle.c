#include "shell.h"

/**
 * long_to_str - function to convert a number to a string.
 * @number: number to convert in a string.
 * @string: buffer to save number as a string.
 * @base: pointer to the base to convert number
 * Return: void
 */
void long_to_str(long number, char *string, int base)
{
	int idx = 0, iNeg = 0;
	long coc = number;
	char letters[] = {"0123456789abcdef"};

	if (coc == 0)
		string[idx++] = '0';

	if (string[0] == '-')
		iNeg = 1;

	while (coc)
	{
		if (coc < 0)
			string[idx++] = letters[-(coc % base)];
		else
			string[idx++] = letters[coc % base];
		coc /= base;
	}
	if (iNeg)
		string[idx++] = '-';

	string[idx] = '\0';
	str_rev(string);
}


/**
 * _atoi - function to convert a string to an integer.
 * @str: pointer to the string origon.
 * Return: int of str or 0.
 */
int _atoi(char *str)
{
	int sig = 1;
	unsigned int num = 0;

	while (!('0' <= *str && *str <= '9') && *str != '\0')
	{
		if (*str == '-')
			sig *= -1;
		if (*str == '+')
			sig *= +1;
		str++;
	}

	while ('0' <= *str && *str <= '9' && *str != '\0')
	{

		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num * sig);
}

/**
 * count_chars - function to count the incidences of character in a str.
 *
 * @string: pointer to str origin
 * @character: str with  chars to be counted
 * Return: int of str or 0.
 */
int count_chars(char *string, char *character)
{
	int u, c = 0;

	for (u = 0; string[u]; u++)
	{
		if (string[u] == character[0])
			c++;
	}
	return (c);
}
