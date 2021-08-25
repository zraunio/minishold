/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:17:31 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/25 09:54:45 by zraunio          ###   ########.fr       */
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

<<<<<<< HEAD
// typedef struct s_shell
// {
// 	char	**env;
// 	char	**tok;
// 	char	**hist;
// 	char	*tok;
// 	t_lexer	*lex;
// 	size_t	n_hist;
// 	char	*hist_path;
// 	int		hist_fd;
// 	char	**hash_str;
// 	char	*hash_one[H_SIZE];
// 	char	buff[MAX_BUFF];
// 	char	**args;
// 	char	**sh_args;
// 	int		n;
// 	int		logo;
// }				t_shell

char	**get_copy_of_environment_variables();
=======
char	**get_copy_of_environment_variables(void);
>>>>>>> main

char	**get_paths_to_array(char **environ);

void	fork_and_child(char **path_array, char **copy_of_environ);

void	loop_input_to_string(char *buf);

char	**split_input_to_array(char *buf);

char	*check_if_built_in(char **buf_arr);

char	*check_if_executable(char **buf_arr, char **path_array);

void	execute_built_in(char *built_in, char **copy_of_environ, char **args);

<<<<<<< HEAD

#endif
=======
void	change_to_uppercase(char *str);

char	*return_string_before_given_character(char *str, char c);

void	set_environment_variable(char **copy_of_environ, char *args);

void	unset_environment_variable(char **copy_of_environ, char *args);

int	check_if_var_is_in_array(char *variable, char **copy_of_environ);

void	ft_putarr(char **arr);

char	*print_text(char *echo_arg);

char	*print_double_quotes(char *echo_arg, char **copy_of_environ);

char	*print_dollar(char **environ, char *echo_arg);

void	remove_one_string_in_array(char **array, int row);

#endif
>>>>>>> main
