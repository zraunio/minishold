/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_something_functions.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 17:49:21 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/30 21:57:18 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*check_if_built_in(char **buf_arr)
{
	int		i;
	char	*if_built_in;
	char	*tmp;

	i = 0;
	if_built_in = return_string_before_given_character(buf_arr[0], ' ');
	if (if_built_in == NULL)
		if_built_in = ft_strdup(buf_arr[0]);
	while (if_built_in[i] == ' ' || if_built_in[i] == '\n' || if_built_in[i]
		== '\t')
		i++;
	tmp = ft_strdup(if_built_in + i);
	free(if_built_in);
	if (ft_strequ("cd", tmp) || ft_strequ("exit", tmp) || ft_strequ("env", tmp)
		|| ft_strequ("unsetenv", tmp) || ft_strequ("setenv", tmp)
		|| ft_strequ("echo", tmp))
		return (tmp);
	return (NULL);
}

char	*check_if_executable(char **buf_arr, char **path_array)
{
	char		*tmp;
	char		*tmp2;
	int			i;
	struct stat	buff;
	char		*if_exec;

	i = 0;
	if_exec = return_string_before_given_character(buf_arr[0], ' ');
	if (if_exec == NULL)
		if_exec = ft_strdup(buf_arr[0]);
	while (path_array[i] != NULL)
	{
		tmp = ft_strjoin(path_array[i], "/");
		tmp2 = ft_strjoin(tmp, if_exec);
		if (lstat(tmp2, &buff) == 0)
		{
			free_two(if_exec, tmp);
			return (tmp2);
		}
		free_two(tmp, tmp2);
		i++;
	}
	ft_printf("zsh: command not found: %s\n", if_exec);
	free(if_exec);
	return (NULL);
}
