/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:17:31 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/17 17:27:26 by ehelmine         ###   ########.fr       */
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

char	**get_copy_of_environment_variables(void);

char	**get_paths_to_array(char **environ);

void	fork_and_child(char **path_array, char **copy_of_environ);

void	loop_input_to_string(char *buf);

char	**split_input_to_array(char *buf);

void	execute_built_in(char *built_in, char **copy_of_environ, char **args);

#endif