/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:17:31 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/26 15:22:07 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <sys/types.h>
# include "../libft/includes/libft.h"
# include "../libft/ft_printf/includes/ft_printf.h"
# include <sys/stat.h>
# include <stdio.h>

typedef	struct	s_shell
{
		char	**copy_of_environ;
		int		num_of_variables;
		int		quote;
}				t_shell;


void	get_copy_of_environment_variables(t_shell *data);

char	**get_paths_to_array(t_shell *data);

void	fork_and_child(char **path_array, t_shell *data);

void	loop_input_to_string(char *buf);

char	**split_input_to_array(char *buf);

char	*check_if_built_in(char **buf_arr);

char	*check_if_executable(char **buf_arr, char **path_array);

void	execute_built_in(char *built_in, t_shell *data, char **args);

void	change_to_uppercase(char *str);

int	check_amount_of_quotes(char *args, t_shell *data);

void	loop_double_quotes(char *args, int am_of_quotes, t_shell *data);

char	*return_string_before_given_character(char *str, char c);

void	check_given_directory(char *args, t_shell *data);

void	set_environment_variable(t_shell *data, char *args);

void	unset_environment_variable(t_shell *data, char *args);

int	check_if_var_is_in_array(char *variable, char **copy_of_environ);

char	*print_text_after_pipe_or_semicolon(char *echo_arg, int quote);

char	*print_quotes(char *echo_arg, char **copy_of_environ, int q_num, char quote);

char	*print_dollar(char **environ, char *echo_arg);

void	remove_one_string_in_array(char **array, int row);

#endif