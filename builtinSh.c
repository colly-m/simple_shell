#include "shell.h"

/**
 * builtin_exit - function to exit the program
 * @data: struct data
 * Return: 0 (success), or other number declared in the arguments
 */
int builtin_exit(data_sh *data)
{
	int i;

	if (data->tokens[1] != NULL)
	{
		for (i = 0; data->tokens[1][i]; i++)
			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
				&& data->tokens[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all(data);
	exit(errno);
}

/**
 * builtin_cd - function to change the current directory
 * @data: pointer to struct data
 * Return: 0 (success), or other number declared in the arguments
 */
int builtin_cd(data_sh *data)
{
	char *dir_home = env_getz("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (str_cmp(data->tokens[1], "-", 0))
		{
			dir_old = env_getz("OLDPWD", data);
			if (dir_old)
				error_code = setz_work_dir(data, dir_old);
			stdout_print(env_getz("PWD", data));
			stdout_print("\n");

			return (error_code);
		}
		else
		{
			return (setz_work_dir(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (setz_work_dir(data, dir_home));
	}
	return (0);
}

/**
 * setz_work_dir - function to set the work directory
 * @data: struct data
 * @new_dir: pointer to new directroy
 * Return: 0 (success), or other number declared in the arguments
 */
int setz_work_dir(data_sh *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_cmp(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_setz("PWD", new_dir, data);
	}
	env_setz("OLDPWD", old_dir, data);
	return (0);
}

/**
 * builtin_help - function where environment shell runs
 * @data: pointer struct data
 * Return: 0 (success), or other number declared in the arguments
 */
int builtin_help(data_sh *data)
{
	int i, length = 0;
	char *messages[6] = {NULL};

	messages[0] = HELP_MSG;

	if (data->tokens[1] == NULL)
	{
		stdout_print(messages[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	messages[1] = HELP_EXIT_MSG;
	messages[2] = HELP_ENV_MSG;
	messages[3] = HELP_SETENV_MSG;
	messages[4] = HELP_UNSETENV_MSG;
	messages[5] = HELP_CD_MSG;

	for (i = 0; messages[i]; i++)
	{
		length = string_len(data->tokens[1]);
		if (str_cmp(data->tokens[1], messages[i], length))
		{
			stdout_print(messages[i] + length + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * getz_builtin_alias - function add, remove or show aliases
 * @data: pointer to struct data
 * Return: 0 (success), or other number declared in the arguments
 */
int builtin_alias(data_sh *data)
{
	int i = 0;

	if (data->tokens[1] == NULL)
		return (func_print_alias(data, NULL));

	while (data->tokens[++i])
	{
		if (count_chars(data->tokens[i], "="))
			func_set_alias(data->tokens[i], data);
		else
			func_print_alias(data, data->tokens[i]);
	}

	return (0);
}
