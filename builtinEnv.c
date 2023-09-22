#include "shell.h"

/**
 * builtin_env - function to get the environment where shell runs
 * @data: pointer struct data
 * Return: 0 (success), or other number if declared in arguments
 */
int builtin_env(data_sh *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	/* if not arguments */
	if (data->tokens[1] == NULL)
		print_env(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{
			if (data->tokens[1][i] == '=')
			{
				var_copy = str_dup(env_getz(cpname, data));
				if (var_copy != NULL)
					env_setz(cpname, data->tokens[1] + i + 1, data);

				print_env(data);
				if (env_getz(cpname, data) == NULL)
				{
					stdout_print(data->tokens[1]);
					stdout_print("\n");
				}
				else
				{
					env_setz(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = data->tokens[1][i];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - function to set buitin environment
 * @data: struct data
 * Return: 0 (success), or other number declared arguments
 */
int builtin_set_env(data_sh *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	env_setz(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * builtin_unset_env - function to unset builtin environment
 * @data: struct data'
 * Return: 0 success
 */
int builtin_unset_env(data_sh *data)
{
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_rm(data->tokens[1], data);

	return (0);
}
