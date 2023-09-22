#include "shell.h"


/**
 * check_prog - function to find program in the path
 * @data: pointer data struct
 * Return: 0 (success),or errcode
 */
int check_prog(data_sh *data)
{
	int i = 0, ret_code = 0;
	char **dir;

	if (!data->command_name)
		return (2);

	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file_path(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_con(str_dup("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	dir = token_path(data);

	if (!dir || !dir[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; dir[i]; i++)
	{
		dir[i] = str_con(dir[i], data->tokens[0]);
		ret_code = check_file_path(dir[i]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_dup(dir[i]);
			free_pointer_array(dir);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_pointer_array(dir);
	return (ret_code);
}

/**
 * token_path - function to tokenizes path in the directories
 * @data: pointer data
 * Return: arrays of path directory
 */
char **token_path(data_sh *data)
{
	int i = 0;
	int c_dir = 2;
	char **tokens = NULL;
	char *PATH;

	PATH = env_getz("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = str_dup(PATH);

	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			c_dir++;
	}

	tokens = malloc(sizeof(char *) * c_dir);

	i = 0;
	tokens[i] = str_dup(_strtok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = str_dup(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * check_file_path - function to check if its a file, if not directory or
 * if it has excecution permisions.
 * @f_path: pointer to the file name
 * Return: 0 (success), or error code if it exists.
 */
int check_file_path(char *f_path)
{
	struct stat sb;

	if (stat(f_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(f_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
