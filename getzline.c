#include "shell.h"

/**
* get_line - function to read a line from the prompt.
* @data: struct for the data
* Return: reading bytes.
*/
int get_line(data_sh *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_cmds[10] = {NULL};
	static char array_ops[10] = {'\0'};
	ssize_t bytes_read, s = 0;

	if (!array_cmds[0] || (array_ops[0] == '&' && errno != 0) ||
		(array_ops[0] == '|' && errno == 0))
	{
		for (s = 0; array_cmds[s]; s++)
		{
			free(array_cmds[s]);
			array_cmds[s] = NULL;
		}

		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		s = 0;
		do {
			array_cmds[s] = str_dup(_strtok(s ? NULL : buff, "\n;"));
			s = sep_log_ops(array_cmds, s, array_ops);
		} while (array_cmds[s++]);
	}

	data->input_line = array_cmds[0];
	for (s = 0; array_cmds[s]; s++)
	{
		array_cmds[s] = array_cmds[s + 1];
		array_ops[s] = array_ops[s + 1];
	}

	return (string_len(data->input_line));
}

/**
 * sep_log_ops - function to check and splits for the && and || operators
 * @array_commands: array commands.
 * @i: index
 * @array_operators: array operators
 * Return: i
*/
int sep_log_ops(char *array_commands[], int i, char array_operators[])
{
	char *tmp = NULL;
	int j;

	for (j = 0; array_commands[i] != NULL  && array_commands[i][j]; j++)
	{
		if (array_commands[i][j] == '&' && array_commands[i][j + 1] == '&')
		{
			tmp = array_commands[i];
			array_commands[i][j] = '\0';
			array_commands[i] = str_dup(array_commands[i]);
			array_commands[i + 1] = str_dup(tmp + j + 2);
			i++;
			array_operators[i] = '&';
			free(tmp);
			j = 0;
		}
		if (array_commands[i][j] == '|' && array_commands[i][j + 1] == '|')
		{
			tmp = array_commands[i];
			array_commands[i][j] = '\0';
			array_commands[i] = str_dup(array_commands[i]);
			array_commands[i + 1] = str_dup(tmp + j + 2);
			i++;
			array_operators[i] = '|';
			free(tmp);
			j = 0;
		}
	}
	return (i);
}
