/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:17:31 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/17 10:14:01 by zraunio          ###   ########.fr       */
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

char	**get_paths_to_array(char **environ);

void	fork_and_child(char **path_array, char **copy_of_environ);

char	**split_input_to_array(char *buf);

void	execute_built_in(char *built_in, char **copy_of_environ, char **args);


#endif
