#include "shell.h"

/**
 * token_char - function to separates the str using a designed delimiter
 * @data: pointer data
 * Return: an array of the different parts of the str
 */
void token_char(data_sh *data)
{
	char *delim = " \t";
	int i, j, c = 2, len;

	len = string_len(data->input_line);
	if (len)
	{
		if (data->input_line[len - 1] == '\n')
			data->input_line[len - 1] = '\0';
	}

	for (i = 0; data->input_line[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (data->input_line[i] == delim[j])
				c++;
		}
	}

	data->tokens = malloc(c * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	i = 0;
	data->tokens[i] = str_dup(_strtok(data->input_line, delim));
	data->command_name = str_dup(data->tokens[0]);
	while (data->tokens[i++])
	{
		data->tokens[i] = str_dup(_strtok(NULL, delim));
	}
}
