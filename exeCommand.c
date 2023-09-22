#include "shell.h"
/**
 * exec_cmd - function to execute a command with its path variables.
 * @data: a pointer data
 * Return: 0 (success),or -1.
 */
int exec_cmd(data_sh *data)
{
	int retval = 0, stat;
	pid_t pid;

	retval = check_builtins_list(data);
	if (retval != -1)
		return (retval);

	retval = check_prog(data);
	if (retval)
	{
		return (retval);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			retval = execve(data->tokens[0], data->tokens, data->env);
			if (retval == -1)
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&stat);
			if (WIFEXITED(stat))
				errno = WEXITSTATUS(stat);
			else if (WIFSIGNALED(stat))
				errno = 128 + WTERMSIG(stat);
		}
	}
	return (0);
}
