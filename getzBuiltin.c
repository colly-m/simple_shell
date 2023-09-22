#include "shell.h"

/**
 * check_builtins_list - function to searche for match and executes
 * the associate builtin
 * @data: pointer to struct data
 * Return: return of the function executed if there's a match,
 * otherwise returns -1.
 **/
int check_builtins_list(data_sh *data)
{
	int itor;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

	for (itor = 0; options[itor].builtin != NULL; itor++)
	{
		if (str_cmp(options[itor].builtin, data->command_name, 0))
		{
			return (options[itor].function(data));
		}
	}
	return (-1);
}
