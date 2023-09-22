#include "shell.h"

/**
 * free_recur_data - function to free the fields needed in each loop
 * @data: pointer struct data
 * Return: void
 */
void free_recur_data(data_sh *data)
{
	if (data->tokens)
		free_pointer_array(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * free_all - function to free all  the field of the data
 * @data: pointer struct data
 * Return: void
 */
void free_all(data_sh *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_recur_data(data);
	free_pointer_array(data->env);
	free_pointer_array(data->alias_list);
}

/**
 * free_pointer_array - function to free each pointer of an array and the
 * array too
 * @array: pointer of arrays
 * Return: void
 */
void free_pointer_array(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}
