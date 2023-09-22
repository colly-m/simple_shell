#include "shell.h"

/**
 * exp_var - function to expand the variables
 * @data: a pointer to a struct data
 * Return: nothing, and sets errno.
 */
void exp_var(data_sh *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expand[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buff_add(line, data->input_line);
	for (i = 0; line[i]; i++)
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			long_to_str(errno, expand, 10);
			buff_add(line, expand);
			buff_add(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			long_to_str(getpid(), expand, 10);
			buff_add(line, expand);
			buff_add(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expand[j - 1] = line[i + j];
			temp = env_getz(expand, data);
			line[i] = '\0', expand[0] = '\0';
			buff_add(expand, line + i + j);
			temp ? buff_add(line, temp) : 1;
			buff_add(line, expand);
		}
	if (!str_cmp(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_dup(line);
	}
}

/**
 * exp_alias - function to expand aliases
 * @data: a pointer to a struct data
 * Return: void
 */
void exp_alias(data_sh *data)
{
	int i, j, was_exp = 0;
	char line[BUFFER_SIZE] = {0}, expand[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buff_add(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expand[j] = line[i + j];
		expand[j] = '\0';

		temp = getz_alias(data, expand);
		if (temp)
		{
			expand[0] = '\0';
			buff_add(expand, line + i + j);
			line[i] = '\0';
			buff_add(line, temp);
			line[string_len(line)] = '\0';
			buff_add(line, expand);
			was_exp = 1;
		}
		break;
	}
	if (was_exp)
	{
		free(data->input_line);
		data->input_line = str_dup(line);
	}
}

/**
 * buff_add - function to append the string on end buffer
 * @buffer: pointer buffer to fill
 * @str_add: string to copy in the buffer
 * Return: length.
 */
int buff_add(char *buffer, char *str_add)
{
	int length, i;

	length = string_len(buffer);
	for (i = 0; str_add[i]; i++)
	{
		buffer[length + i] = str_add[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}
