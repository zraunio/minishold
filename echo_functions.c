/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 17:46:40 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/07 17:30:29 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	write_echo_output(char *echo_arg, int output_len, int in_or_out,
	int quote)
{
	int	i;

	i = 0;
	while (echo_arg[i] != '\0' && i < output_len)
	{
		while (echo_arg[i] == '\\')
		{
			if (in_or_out == 2 && (echo_arg[i + 1] == 'n'
					|| (echo_arg[i + 1] == '\\' && echo_arg[i + 2] == 'n')
					|| echo_arg[i + 1] == 't' || (echo_arg[i + 1] == '\\'
						&& echo_arg[i + 2] == 't')))
			{
				if (echo_arg[i + 1] == 'n' || echo_arg[i + 2] == 'n')
					write(1, "\n", 1);
				else if (echo_arg[i + 1] == 't' || echo_arg[i + 2] == 't')
					write(1, "\t", 1);
				if (echo_arg[i + 1] == '\\' && (echo_arg[i + 2] == 'n'
						|| echo_arg[i + 2] == 't'))
					i++;
				i += 2;
			}
			else if (in_or_out == 0)
			{
				if (echo_arg[i + 1] == '\\' && (echo_arg[i + 2] == 'n'
						|| echo_arg[i + 2] == 't'))
				{
					if (echo_arg[i + 2] == 'n')
						write(1, "\n", 1);
					else if (echo_arg[i + 2] == 't')
						write(1, "\t", 1);
					i += 3;
				}
			}
			else if (in_or_out == 2)
			{
				i++;
				if (echo_arg[i + 1] == ' ')
					write(1, &echo_arg[i++], 1);
			}
		}
		if ((echo_arg[i] == '"' && (quote == 2 || quote == 0))
			|| (echo_arg[i] == '\'' && (quote == 1 || quote == 0))
			|| echo_arg[i] == '\0')
			break ;
		write(1, &echo_arg[i++], 1);
	}
}

char	*print_dollar(char **environ, char *echo_arg, char *temp)
{
	int		i;
	int		len;
	int		x;
	char	*check;

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

char	*print_quotes(char *echo_arg, char **copy_of_environ, int q_num,
	char quote)
{
	int	i;

	i = 0;
	if (echo_arg[i + 1] == '\0')
	{
		if ((quote == '"' && echo_arg[i] == '"' && q_num != 1)
			|| (quote == '\'' && echo_arg[i] == '\'' && q_num != 2))
			write(1, "\n", 1);
		return (echo_arg + 1);
	}
	while (echo_arg[i] != '\0')
	{
		if (echo_arg[i] == '$')
		{
			if (i > 1)
				write_echo_output(echo_arg, i, 2, q_num);
			echo_arg = print_dollar(copy_of_environ, echo_arg + i + 1, NULL);
			if (echo_arg[0] == '\0')
				return (echo_arg);
			i = -1;
		}
		else if ((quote == '"' && echo_arg[i] == '"' && q_num == 2
				&& echo_arg[i - 1] != '\\') || (quote == '\''
				&& echo_arg[i] == '\'' && q_num == 1))
			break ;
		i++;
	}
	if (i == 0)
		return (echo_arg);
	write_echo_output(echo_arg, i, 2, q_num);
	return (echo_arg + i + 1);
}

char	*print_text_after_pipe_or_semicolon(char *echo_arg, int quote)
{
	int	i;

	i = 0;
	while (echo_arg[i] != '\0')
	{
		if (echo_arg[i] == '"' || echo_arg[i] == '\'' || echo_arg[i] == '$')
			break ;
		i++;
	}
	write_echo_output(echo_arg, i, 0, quote);
	return (echo_arg + i);
}
