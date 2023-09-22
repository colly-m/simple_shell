#ifndef SHELL_H
#define SHELL_H

#include "macros.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>


/**
 * struct info- struct for the data
 * @program_name: name of the executable
 * @input_line: pointer of the input read for get_line
 * @command_name: pointer of the first command typed
 * @exec_counter: number of excecuted commands
 * @file_descriptor: filedescriptor
 * @tokens: pointer to array of tokens
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_sh;



int builtin_exit(data_sh *data);
int builtin_help(data_sh *data);
int builtin_cd(data_sh *data);
int builtin_alias(data_sh *data);
int builtin_env(data_sh *data);
int builtin_set_env(data_sh *data);
int builtin_unset_env(data_sh *data);


/**
 * struct builtins - struct of the builtins
 * @builtin: the name of the builtin
 * @function: function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_sh *data);
} builtins;




/* shell.c */

void init_data(data_sh *data, int argc, char *argv[], char **env);

void sh_loop(char *prompt, data_sh *data);

void print_prompt(int opr UNUSED);


/* getzline.c */

int get_line(data_sh *data);

int sep_log_ops(char *array_cmd[], int i, char array_opera[]);


/* sizeUp.c */

void exp_var(data_sh *data);

void exp_alias(data_sh *data);

int buff_add(char *buffer, char *str_add);


/* sepChars.c */

void token_char(data_sh *data);


/* strToken.c */

char *_strtok(char *line, char *delim);


/* execCommand.c */

int exec_cmd(data_sh *data);


/* getzBuiltin.c */

int check_builtins_list(data_sh *data);


/* pathFinder.c */

char **token_path(data_sh *data);

int check_prog(data_sh *data);

int check_file_path(char *f_path);


/* freeup.c */

void free_pointer_array(char **array);

void free_recur_data(data_sh *data);

void free_all(data_sh *data);



/* builtinSh.c */

int builtin_exit_prog(data_sh *data);

int builtin_cd_slash(data_sh *data);

int setz_work_dir(data_sh *data, char *new_dir);

int builtin_help_env(data_sh *data);

int getz_builtin_alias(data_sh *data);


/* builtinEnv.c */

int builtin_env(data_sh *data);

int builtin_set_env(data_sh *data);

int builtin_unset_env(data_sh *data);



/* envHandle.c */

char *env_getz(char *name, data_sh *data);

int env_setz(char *key, char *value, data_sh *data);

int env_rm(char *key, data_sh *data);

void print_env(data_sh *data);



/* getzstdPrint.c */

int stdout_print(char *string);

int stderr_print(char *string);

int std_print_err(int errorcode, data_sh *data);



/* firststrHandle.c */

int string_len(char *string);

char *str_dup(char *string);

int str_cmp(char *string1, char *string2, int number);

char *str_con(char *string1, char *string2);

void str_rev(char *string);


/* strnumHandle.c */

void long_to_str(long number, char *string, int base);

int _atoi(char *s);

int count_chars(char *string, char *character);


/* akaHandle.c */

int func_print_alias(data_sh *data, char *alias);

char *getz_alias(data_sh *data, char *name);

int func_set_alias(char *alias_str, data_sh *data);


#endif
