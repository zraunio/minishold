/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:18:22 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/08 16:15:50 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*my_echo_loop_text(char *arg, t_shell *data, int visit)
{
	if (visit)
		write(1, " ", 1);
	return (print_text(arg + data->i, data->quote));
}

static char	*my_echo_loop_quote(char *arg, t_shell *data, int visit)
{
	if (visit)
		write(1, " ", 1);
	if ((arg[data->i] == '"' && arg[data->i + 1] == '"')
		|| (arg[data->i] == '\'' && arg[data->i + 1] == '\''))
		return (arg + 2);
	return (print_quotes(arg + data->i + 1, data->environ, data->quote,
					arg[data->i]));
	
}

static char	*my_echo_loop_dollar(char *arg, t_shell *data, int visit)
{
	if (visit)
		write(1, " ", 1);
	return (print_dollar(data->environ, arg + data->i + 1, NULL));
}

static void	my_echo_loop(char *arg, t_shell *data, int visit)
{
	while (arg[data->i] != '\0')
	{
		while (arg[data->i] == ' ')
			data->i++;
		if (arg[data->i] == '$')
		{
			arg = my_echo_loop_dollar(arg, data, visit);
			visit = 1;
		}
		else if ((arg[data->i] == '"' && (data->quote == 2
					|| data->quote == 0)) || (arg[data->i] == '\''
				&& (data->quote == 1 || data->quote == 0)))
		{
			arg = my_echo_loop_quote(arg, data, visit);
			visit = 1;
		}
		else if (arg[data->i] != '|' || arg[data->i] != ';')
		{
			arg = my_echo_loop_text(arg, data, visit);
			visit = 1;
		}
		data->i = 0;
	}
}

void	my_echo(char *echo_arg, t_shell *data)
{
	if (echo_arg != NULL)
	{
		data->i = 0;
		my_echo_loop(echo_arg, data, 0);
	}
	if (!data->n_flag)
		write(1, "\n", 1);
	return ;
}
