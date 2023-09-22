#include "shell.h"

/**
 * env_getz - gets a value of the environment variable
 * @key: the environment variable
 * @data: struct data
 * Return: a pointer to the value of the variable or NULL
 */
char *env_getz(char *key, data_sh *data)
{
	int i, key_len = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);

	key_len = string_len(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_cmp(key, data->env[i], key_len) &&
		 data->env[i][key_len] == '=')
		{
			return (data->env[i] + key_len + 1);
		}
	}
	return (NULL);
}

/**
 * env_setz - overwrites value of the environment variable
 * or create it if does not exist.
 * @key: variable to set
 * @value: value
 * @data: struct data
 * Return: 1 on NULL parameters, 2 if there is an error 0 (success).
 */

int env_setz(char *key, char *value, data_sh *data)
{
	int i, key_len = 0, nw_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	key_len = string_len(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_cmp(key, data->env[i], key_len) &&
		 data->env[i][key_len] == '=')
		{
			nw_key = 0;

			free(data->env[i]);
			break;
		}
	}

	data->env[i] = str_con(str_dup(key), "=");
	data->env[i] = str_con(data->env[i], value);

	if (nw_key)
	{
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * env_rm - function to remove key from the environment
 * @key: pointer to key to be remove
 * @data: pointer the sructure of data
 * Return: 1 if key is removed, 0 if key doesn't exist;
 */
int env_rm(char *key, data_sh *data)
{
	int i, key_len = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	key_len = string_len(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_cmp(key, data->env[i], key_len) &&
		 data->env[i][key_len] == '=')
		{
			free(data->env[i]);

			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}

			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_env - function to print the environment
 * @data: struct data
 * Return: void
 */
void print_env(data_sh *data)
{
	int k;

	for (k = 0; data->env[k]; k++)
	{
		stdout_print(data->env[k]);
		stdout_print("\n");
	}
}
