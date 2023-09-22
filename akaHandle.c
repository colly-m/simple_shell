#include "shell.h"

/**
 * func_print_alias - function to add, remove or show aliases
 * @data: struct data
 * @alias: alias to print
 * Return: 0 (success), or other number if declared in arguments
 */
int func_print_alias(data_sh *data, char *alias)
{
	int i, j, alias_len;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_len = string_len(alias);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias || (str_cmp(data->alias_list[i], alias, alias_len)
				&&	data->alias_list[i][alias_len] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buff_add(buffer, "'");
				buff_add(buffer, data->alias_list[i] + j + 1);
				buff_add(buffer, "'\n");
				stdout_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * getz_alias - function to add, remove or show aliases
 * @data: pouinter to struct data
 * @name: pointer to requested alias.
 * Return: 0 (success), or other number if declared in arguments
 */
char *getz_alias(data_sh *data, char *name)
{
	int i, alias_len;

	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_len = string_len(name);

	for (i = 0; data->alias_list[i]; i++)
	{
		if (str_cmp(name, data->alias_list[i], alias_len) &&
			data->alias_list[i][alias_len] == '=')
		{
			return (data->alias_list[i] + alias_len + 1);
		}
	}

	return (NULL);
}

/**
 * func_set_alias - function to add, or override alias
 * @alias_str: alias string
 * @data: struct data
 * Return: 0 (success), or other number declared in the arguments
 */
int func_set_alias(char *alias_str, data_sh *data)
{
	int i, j;
	char buf[250] = {'0'}, *tmp = NULL;

	if (alias_str == NULL ||  data->alias_list == NULL)
		return (1);

	for (i = 0; alias_str[i]; i++)
		if (alias_str[i] != '=')
			buf[i] = alias_str[i];
		else
		{
			tmp = getz_alias(data, alias_str + i + 1);
			break;
		}

	for (j = 0; data->alias_list[j]; j++)
		if (str_cmp(buf, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{
			free(data->alias_list[j]);
			break;
		}

	if (tmp)
	{
		buff_add(buf, "=");
		buff_add(buf, tmp);
		data->alias_list[j] = str_dup(buf);
	}
	else
		data->alias_list[j] = str_dup(alias_str);
	return (0);
}
