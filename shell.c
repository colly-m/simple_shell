#include "shell.h"
/**
 * main - entry point
 * @argc: pointer to argument count
 * @argv: poinetr to argument vector
 * @env: pointer to environment values
 * Return:0 on (success).
 */
int main(int argc, char *argv[], char *env[])
{
	data_sh data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	init_data(data, argc, argv, env);

	signal(SIGINT, print_prompt);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* We are in the terminal, interactive mode */
		errno = 2;/*???????*/
		prompt = PROMPT_MSG;
	}
	errno = 0;
	sh_loop(prompt, data);
	return (0);
}

/**
 * print_prompt - function to prints prompt of a new line
 * when the signal SIGINT (ctrl + c) is sent to the program
 * @UNUSED: option of the prototype
 */
void print_prompt(int opr UNUSED)
{
	stdout_print("\n");
	stdout_print(PROMPT_MSG);
}

/**
 * init_data - initializes the struct with the info
 * @data: pointer to data
 * @argv: array of arguments passed to the program exec
 * @env: environ passed to the program exec
 * @argc: values received from the command line
 */
void init_data(data_sh *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;

	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			stderr_print(data->program_name);
			stderr_print(": 0: Can't open ");
			stderr_print(argv[1]);
			stderr_print("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_dup(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}
/**
 * sh_loop - its a loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: its a loop that shows the prompt
 */
void sh_loop(char *prompt, data_sh *data)
{
	int err_code = 0, str_len = 0;

	while (++(data->exec_counter))
	{
		stdout_print(prompt);
		err_code = str_len = get_line(data);

		if (err_code == EOF)
		{
			free_all(data);
			exit(errno);
		}
		if (str_len >= 1)
		{
			exp_alias(data);
			exp_var(data);
			token_char(data);
			if (data->tokens[0])
			{
				err_code = exec_cmd(data);
				if (err_code != 0)
					std_print_err(err_code, data);
			}
			free_recur_data(data);
		}
	}
}
