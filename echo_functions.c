/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 17:46:40 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/17 17:46:59 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*print_dollar(char **environ, char *echo_arg)
{
	int i;
	int len;
	char *temp;
	int x;
	char *check;

	i = 0;
	if (echo_arg[i] == ' ')
		return (echo_arg);
	while (echo_arg[i] != ' ' && echo_arg[i] != '"' && echo_arg[i] != '\n'
		&& echo_arg[i] != '\0')
		i++;
	temp = NULL;
	temp = ft_strndup(echo_arg, i);
	change_to_uppercase(temp);
	i = 0;
	len = ft_strlen(temp);
	while (environ[i] != NULL)
	{
		check = ft_strstr(environ[i], temp);
		if (check != NULL)
		{
			x = 0;
			if (ft_strcmp(temp, "PATH") == 0)
			{
				free(temp);
				temp = ft_strdup(environ[i] + (ft_strlen(temp) + 1));
				while (temp[x] != '\0')
				{
					if (temp[x] == ':')
						temp[x] = ' ';
					x++;
				}
				ft_putstr(temp);
			}
			else
				ft_putstr(environ[i] + ft_strlen(temp) + 1);
			break ;
		}
		else
			i++;
	}
	free(temp);
	temp = NULL;
	if (echo_arg[len] == '"')
		len++;
	if (environ[i] == NULL && echo_arg[len - 1] == '"')
		write(1, " ", 1);	
	return (echo_arg + len);	
}

char	*print_double_quotes(char *echo_arg, char **copy_of_environ)
{
	int i;

	i = 0;
	if (echo_arg[i] == '"' && echo_arg[i + 1] == '\0')
	{
		write(1, "\n", 1);
		return (echo_arg + 1);
	}
	while (echo_arg[i] != '\0')
	{
		if (echo_arg[i] == '$')
		{
			if (i > 1)
				write(1, echo_arg, i);
			echo_arg = print_dollar(copy_of_environ, echo_arg + i + 1);
			if (echo_arg[0] == '\0')
				return (echo_arg);
			i = -1;
		}
		else if (echo_arg[i] == '"')
			break ;
		i++;
	}
	if (i == 0)
		return (echo_arg);
	write(1, echo_arg, i);
	return (echo_arg + i + 1);
}

char	*print_text(char *echo_arg)
{
	int i;

	i = 0;
	while (echo_arg[i] != '\0')
	{
		if (echo_arg[i] == '"' || echo_arg[i] == '$')
			break ;
		i++;
	}
	if (i < (int)ft_strlen(echo_arg))
		write(1, echo_arg, i);
	else
		ft_putstr(echo_arg);
	return (echo_arg + i);
}
