/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 17:46:40 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/10 17:09:17 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*print_dollar(char **environ, char *echo_arg, char *temp)
{
	int		i;
	int		len;

	i = 0;
	if (echo_arg[i] == '\0')
	{
		write(1, "$", 1);
		return (echo_arg);
	}
	if (echo_arg[i] == ' ')
		return (echo_arg);
	while (echo_arg[i] != ' ' && echo_arg[i] != '"' && echo_arg[i] != '\n'
		&& echo_arg[i] != '\0')
		i++;
	temp = ft_strndup(echo_arg, i);
	change_to_uppercase(temp);
	i = 0;
	len = ft_strlen(temp);
	while (environ[i] != NULL)
	{
		if (ft_strstr(environ[i], temp) != NULL)
		{
			ft_putstr(environ[i] + ft_strlen(temp) + 1);
			break ;
		}
		i++;
	}
	ft_memdel((void *)&temp);
	if (echo_arg[len] == '"')
		len++;
	if (environ[i] == NULL && echo_arg[len - 1] == '"')
		write(1, " ", 1);
	return (echo_arg + len);
}

char	*print_quotes(char *echo_arg, char **environ, int q_num,
	char quote)
{
	int	i;

	i = 0;
	while (echo_arg[i] != '\0')
	{
		if (echo_arg[i] == '$')
		{
			if (i > 1)
				write_echo_output(echo_arg, i, 2, q_num);
			echo_arg = print_dollar(environ, echo_arg + i + 1, NULL);
			if (echo_arg[0] == '\0')
				return (echo_arg);
			i = -1;
		}
		else if (echo_arg[i] == quote)
			break ;
		i++;
	}
	if (i == 0)
		return (echo_arg);
	write_echo_output(echo_arg, i, 2, q_num);
	return (echo_arg + i + 1);
}

char	*print_text(char *echo_arg, int quote)
{
	int	i;

	i = 0;
	while (echo_arg[i] != '\0')
	{
		if (echo_arg[i] == '$')
			break ;
		if ((echo_arg[i] == '"' || echo_arg[i] == '\'')
			&& echo_arg[i - 1] != '\\')
			break ;
		i++;
	}
	write_echo_output(echo_arg, i, 0, quote);
	return (echo_arg + i);
}
