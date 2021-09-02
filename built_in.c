/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:57:03 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/01 17:18:44 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	my_echo(char *input, t_shell *data)
{
	int		i;
	char	*echo_arg;
	int		n_flag;

	i = 0;
	n_flag = 0;
	while (input[i] == ' ' && input[i] != '\0')
		i++;
	input += i;
	echo_arg = ft_strstr(input, " ");
	if (echo_arg == NULL && input[4] == '\0')
		return ((void)write(1, "\n", 1));
	if (echo_arg[1] == '-' && echo_arg[2] == 'n')
	{
		if (echo_arg[3] == '\0')
			return ;
		if (echo_arg[3] == ' ')
		{
			n_flag = 1;
			echo_arg = ft_strstr(input + 5, " ");
		}
	}
	if (echo_arg != NULL)
	{
		i = 0;
		while (echo_arg[i] != '\0')
		{
			while (echo_arg[i] == ' ')
				i++;
			if (echo_arg[i] == '$')
				echo_arg = print_dollar(data->copy_of_environ, echo_arg + i
						+ 1);
			else if ((echo_arg[i] == '"' && (data->quote == 2 || data->quote
						== 0)) || (echo_arg[i] == '\'' && (data->quote == 1
						|| data->quote == 0)))
				echo_arg = print_quotes(echo_arg + i + 1,
						data->copy_of_environ, data->quote, echo_arg[i]);
			else if (echo_arg[i] != '|' || echo_arg[i] != ';')
				echo_arg = print_text_after_pipe_or_semicolon(echo_arg + i,
						data->quote);
			i = 0;
		}
	}
	if (!n_flag)
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
	int	i;
	int	am_of_quotes;

	i = 0;
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
		my_echo(args[0], data);
	}
	else if (built_in[0] == 's')
		set_environment_variable(data, args[0]);
	else if (built_in[0] == 'u')
		unset_environment_variable(data, args[0]);
	else
		ft_putarr(data->copy_of_environ);
}
