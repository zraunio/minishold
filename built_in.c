/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:57:03 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/04 15:36:25 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	my_echo(char *echo_arg, t_shell *data)
{
	if (echo_arg != NULL)
	{
		data->i = 0;
		while (echo_arg[data->i] != '\0')
		{
			while (echo_arg[data->i] == ' ')
				data->i++;
			if (echo_arg[data->i] == '$')
				echo_arg = print_dollar(data->copy_of_environ, echo_arg
						+ data->i + 1);
			else if ((echo_arg[data->i] == '"' && (data->quote == 2
						|| data->quote == 0)) || (echo_arg[data->i] == '\''
					&& (data->quote == 1 || data->quote == 0)))
				echo_arg = print_quotes(echo_arg + data->i + 1,
						data->copy_of_environ, data->quote, echo_arg[data->i]);
			else if (echo_arg[data->i] != '|' || echo_arg[data->i] != ';')
				echo_arg = print_text_after_pipe_or_semicolon(echo_arg
						+ data->i, data->quote);
			data->i = 0;
		}
	}
	if (!data->n_flag)
		write(1, "\n", 1);
	return ;
}

/*
** We know now which built_in we are gonna execute, so here we are going
** to check which one it was based on the first and second character of
** the string that contains that built_in (char *built_in).
** Based on that then we are going to call specific function to do what we
** want.
*/

void	execute_built_in(char *built_in, t_shell *data, char **args)
{
	int		am_of_quotes;
	char	*tmp;

	if (built_in[0] == 'e' && built_in[1] == 'x')
		exit (0);
	else if (built_in[0] == 'c')
		cd_function_start(args[0], data);
	else if (built_in[0] == 'e' && built_in[1] == 'c')
	{
		data->quote = 0;
		am_of_quotes = check_amount_of_quotes(args[0], data);
		if (am_of_quotes % 2 != 0)
			loop_double_quotes(args[0], am_of_quotes, data);
		data->n_flag = 0;
		tmp = check_echo_flags_and_skip_whitespaces(args[0], data);
		if (tmp != NULL)
			my_echo(tmp, data);
	}
	else if (built_in[0] == 's')
		set_environment_variable(data, args[0]);
	else if (built_in[0] == 'u')
		unset_environment_variable(data, args[0]);
	else
		ft_putarr(data->copy_of_environ);
}
