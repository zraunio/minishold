/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:17:31 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/07 13:19:51 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <sys/types.h>
# include "../libft/includes/libft.h"
# include "../libft/ft_printf/includes/ft_printf.h"
# include <sys/stat.h>

typedef struct s_shell
{
	char	**copy_of_environ;
	char	**path_array;
	int		num_of_variables;
	int		quote;
	char	**prev_dirs;
	int		l_flag;
	int		p_flag;
	int		n_flag;
	int		i;
	int		x;
	int		len_of_dir;
	int		previous_dir_in_cd;
	char	*original_exec;
}				t_shell;

void	get_copy_of_environment_variables(t_shell *data);
void	get_paths_to_array(t_shell *data);
void	update_path_array(t_shell *data);

void	while_loop_input(t_shell *data);
void	fork_and_child(t_shell *data, char *executable, char **buf_arr);
char	**add_exec_to_arr(char **arr, char *executable);

void	loop_input_to_string(char *buf);
char	check_quotes_for_input(char *buf);
void	loop_more_quotes(char *buf, char quote);
char	**split_input_to_array(char *buf);
void	check_input_array(char **buf_arr);

char	*check_if_built_in(char **buf_arr);
char	*check_if_executable(char **buf_arr, t_shell *data);
char	*check_echo_flags_and_skip_whitespaces(char *input, t_shell *data);

void	execute_built_in(char *built_in, t_shell *data, char **args);

int		check_amount_of_quotes(char *args, t_shell *data);
void	loop_double_quotes(char *args, int am_of_quotes, t_shell *data);

void	cd_function_start(char *args, t_shell *data);
int		check_cd_arguments(char *args, t_shell *data);
void	cd_function_finish(char *current_dir, char *new_dir, t_shell *data,
			char *org_input);
char	*get_current_dir(void);
void	change_directories(t_shell *data, char *new_dir, char *current_dir,
			char *org_input);

void	set_environment_variable(t_shell *data, char *args);
void	unset_environment_variable(t_shell *data, char *args);
void	add_new_var_to_environ(t_shell *data, char *var, char *value);
void	change_old_var_value(t_shell *data, char *var, char *value, int i);
int		check_if_var_is_in_array(char *variable, char **copy_of_environ);

char	*print_text_after_pipe_or_semicolon(char *echo_arg, int quote);
char	*print_quotes(char *echo_arg, char **copy_of_environ, int q_num,
			char quote);
char	*print_dollar(char **environ, char *echo_arg);

void	remove_one_string_in_array(char **array, int row);
char	*return_string_before_given_char(char *str, char c);
void	change_to_uppercase(char *str);

#endif