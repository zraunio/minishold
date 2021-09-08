/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:57:03 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/08 19:06:44 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	execute_built_in_2(char *built_in, t_shell *data, char **args)
{
	if (built_in[0] == 's')
	{
		if (built_in[6] == '\0')
			return ;
		set_environment_variable(data, args[0]);
	}
	else if (built_in[0] == 'u')
	{
		if (built_in[8] == '\0')
			return ;
		unset_environment_variable(data, args[0]);
	}
	else
		ft_putarr(data->environ);
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
		tmp = check_echo_flags_and_skip_whitespaces(args[0], data, 0);
		if (tmp == NULL)
			return ((void)write(1, "\n", 1));
		my_echo(tmp, data);
	}
	else
		return (execute_built_in_2(built_in, data, args));
}
