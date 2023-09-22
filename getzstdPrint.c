#include "shell.h"

/**
 * stdout_print - function to write an array of chars of the standard output
 * @string: pointer to the array of charactors
 * Return: the number of bytes written or .
 * On error, -1 return, and errno is set appropriately.
 */
int stdout_print(char *string)
{
	return (write(STDOUT_FILENO, string, string_len(string)));
}
/**
 * stderr_print - function to  write an array of chars of the standard error
 * @string: pointer to the array of charactors
 * Return: the number of bytes written.
 * On error, -1 return, and errno is set appropriately.
 */
int stderr_print(char *string)
{
	return (write(STDERR_FILENO, string, string_len(string)));
}

/**
 * std_print_err - writes an array of chars in the standard error
 * @data: a pointer data'
 * @errorcode: error code to be printed
 * Return: the number of bytes written or .
 * On error, -1 return, and errno is set appropriately.
 */
int std_print_err(int errorcode, data_sh *data)
{
	char nas_str[10] = {'\0'};

	long_to_str((long) data->exec_counter, nas_str, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		stderr_print(data->program_name);
		stderr_print(": ");
		stderr_print(nas_str);
		stderr_print(": ");
		stderr_print(data->tokens[0]);
		if (errorcode == 2)
			stderr_print(": Illegal number: ");
		else
			stderr_print(": can't cd to ");
		stderr_print(data->tokens[1]);
		stderr_print("\n");
	}
	else if (errorcode == 127)
	{
		stderr_print(data->program_name);
		stderr_print(": ");
		stderr_print(nas_str);
		stderr_print(": ");
		stderr_print(data->command_name);
		stderr_print(": not found\n");
	}
	else if (errorcode == 126)
	{
		stderr_print(data->program_name);
		stderr_print(": ");
		stderr_print(nas_str);
		stderr_print(": ");
		stderr_print(data->command_name);
		stderr_print(": Permission denied\n");
	}
	return (0);
}
