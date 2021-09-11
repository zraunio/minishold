/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 17:46:40 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/11 15:16:45 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*print_dollar(char **environ, char *echo_arg, char *temp)
{
	int		i;
	int		len;

	i = 0;
	if (echo_arg[i] == '\0')
		write(1, "$", 1);
	if (echo_arg[i] == ' ' || echo_arg[i] == '\0')
		return (echo_arg);
	while (echo_arg[i] != ' ' && echo_arg[i] != '"' && echo_arg[i] != '\n'
		&& echo_arg[i] != '\0')
		i++;
	temp = ft_strndup(echo_arg, i);
	len = ft_strlen(temp);
	i = check_if_var_is_in_array(temp, environ);
	if (i != -1)
		ft_putstr(environ[i] + len + 1);
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
