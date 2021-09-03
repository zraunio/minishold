/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_something_functions.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 17:49:21 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/03 16:57:11 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*check_if_built_in(char **buf_arr)
{
	int		i;
	char	*if_built_in;
	int		len;

	i = 0;
	while (ft_isspace(buf_arr[0][i]) && buf_arr[0][i] != '\0')
		i++;
	len = 0;
	while (!ft_isspace(buf_arr[0][i + len]) && buf_arr[0][i + len] != '\0')
		len++;
	if_built_in = return_string_before_given_character(buf_arr[0] + i,
		buf_arr[0][i + len]);
	if (if_built_in == NULL)
	{
		ft_printf("didnt find character\n");
		if_built_in = ft_strdup(buf_arr[0]);
	}
	if (ft_strequ("cd", if_built_in) || ft_strequ("exit", if_built_in)
		|| ft_strequ("env", if_built_in) || ft_strequ("unsetenv", if_built_in)
		|| ft_strequ("setenv", if_built_in) || ft_strequ("echo", if_built_in))
		return (if_built_in);
	free(if_built_in);
	return (NULL);
}

int		only_slashes_and_dots(char *command)
{
	int i;

	i = 0;
	if (ft_strequ(command, "."))
	{
		ft_printf(".: not enough arguments\n");
		free(command);
		return (-1);
	}
	while (command[i] != '\0')
	{
		if (command[i] != '.' && command[i] != '/')
			return (1);
		i++;
	}
	free(command);
	return (-1);
}

char	*check_if_executable(char **buf_arr, t_shell *data)
{
	char		*tmp;
	char		*tmp2;
	int			i;
	struct stat	b;
	char		*if_exec;
	int			len;

	i = 0;
	while (ft_isspace(buf_arr[0][i]) && buf_arr[0][i] != '\0')
		i++;
	len = 0;
	while (!ft_isspace(buf_arr[0][i + len]) && buf_arr[0][i + len] != '\0')
		len++;
	if_exec = return_string_before_given_character(buf_arr[0] + i,
		buf_arr[0][i + len]);
	if (if_exec == NULL)
	{
		ft_printf("didnt find character\n");
		if_exec = ft_strdup(buf_arr[0]);
	}
	if (only_slashes_and_dots(if_exec) == -1)
		return (NULL);
	if (lstat(if_exec, &b) == 0 && b.st_mode & S_IXUSR && S_ISREG(b.st_mode))
		return (if_exec);
	i = 0;
	while (data->path_array[i] != NULL)
	{
		tmp = ft_strjoin(data->path_array[i], "/");
		tmp2 = ft_strjoin(tmp, if_exec);
		if (lstat(tmp2, &b) == 0)
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
