#include "shell.h"

/**
 * string_len - function to return length of a string.
 * @string: pointer to the string.
 * Return: length of the string.
 */
int string_len(char *string)
{
	int len = 0;

	if (string == NULL)
		return (0);

	while (string[len++] != '\0')
	{
	}
	return (--len);
}

/**
 * str_dup - function to duplicates a string
 * @string: String to copy
 * Return: pointer to array
 */
char *str_dup(char *string)
{
	char *res;
	int len, i;

	if (string == NULL)
		return (NULL);

	len = string_len(string) + 1;

	res = malloc(sizeof(char) * len);

	if (res == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < len ; i++)
	{
		res[i] = string[i];
	}

	return (res);
}

/**
 * str_cmp - function to compare the two strings
 * @string1: String one, or the shorter one
 * @string2: String two, or the longer one
 * @number: number of characters to compare, 0 if infinite
 * Return: 1 if the str are equals,0 if the str are different
 */
int str_cmp(char *string1, char *string2, int number)
{
	int itor;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0)
	{
		if (string_len(string1) != string_len(string2))
			return (0);
		for (itor = 0; string1[itor]; itor++)
		{
			if (string1[itor] != string2[itor])
				return (0);
		}
		return (1);
	}
	else
	{
		for (itor = 0; itor < number ; itor++)
		{
			if (string1[itor] != string2[itor])
			return (0);
		}
		return (1);
	}
}

/**
 * str_con - concatenates the two strings.
 * @string1: String to concatenate
 * @string2: String to concatenate
 *
 * Return: pointer to the array
 */
char *str_con(char *string1, char *string2)
{
	char *res;
	int len1 = 0, len2 = 0;

	if (string1 == NULL)
		string1 = "";
	len1 = string_len(string1);

	if (string2 == NULL)
		string2 = "";
	len2 = string_len(string2);

	res = malloc(sizeof(char) * (len1 + len2 + 1));
	if (res == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (len1 = 0; string1[len1] != '\0'; len1++)
		res[len1] = string1[len1];
	free(string1);

	for (len2 = 0; string2[len2] != '\0'; len2++)
	{
		res[len1] = string2[len2];
		len1++;
	}

	res[len1] = '\0';
	return (res);
}


/**
 * str_rev - reverses the string.
 *
 * @string: pointer string.
 * Return: void.
 */
void str_rev(char *string)
{

	int i = 0, len = string_len(string) - 1;
	char tmp;

	while (i < len)
	{
		tmp = string[i];
		string[i++] = string[len];
		string[len--] = tmp;
	}
}
