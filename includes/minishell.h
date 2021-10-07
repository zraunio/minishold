/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:17:31 by ehelmine          #+#    #+#             */
/*   Updated: 2021/10/07 11:01:18 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <sys/types.h>
# include "../libft/incl/libft.h"
# include "echo.h"
# include "cd.h"
# include "setenv.h"
# include <sys/stat.h>

typedef struct s_shell
{
	char		**environ;
	char		**path_array;
	int			num_of_variables;
	int			quote;
	char		**prev_dirs;
	int			l_flag;
	int			p_flag;
	int			n_flag;
	int			cd_previous_dir;
	char		*prev_dir;
	char		*original_exec;
	int			visit;
	size_t		i;
	size_t		x;
	size_t		len_of_dir;
}				t_shell;

void		get_copy_of_environment_variables(t_shell *data);
char		**get_paths_to_array(t_shell *data);
void		fork_and_child(t_shell *data, char *executable, char **buf_arr);
void		loop_input_to_string(char *buf);
char	**split_input_to_array(char *buf, int i);

char		*check_if_built_in(char **buf_arr);
char		*check_if_executable(char **buf_arr, char **path_array, size_t len);
char		*check_echo_flags_and_skip_whitespaces(char *input, t_shell *data,
				int i);
char		*check_if_exec_with_quotes(char *if_exec, t_shell *data);

void		execute_built_in(char *built_in, t_shell *data, char **args);

int			check_amount_of_quotes(char *args, t_shell *data);
void		loop_double_quotes(char *args, int am_of_quotes, t_shell *data);

char		*get_current_dir(void);
void		change_directories(t_shell *data, char *new_dir, char *current_dir, char *org_input);

long long	check_if_array(char *var, char **env);

char		*print_text_after_pipe_or_semicolon(char *echo_arg, int quote);
char		*print_quotes(char *out, char **env, int n, char q);
char		*print_dollar(char **env, char *out);

void		remove_one_string_in_array(char **array, int row);
char		*return_string_before_given_character(char *str, char c);
void		change_to_uppercase(char *str);
void		check_if_null_ptr(void *ptr);
void		check_if_null_arr(void **arr);
int			check_quotes_with_semicolon(char *str, int len, int i);

#endif
