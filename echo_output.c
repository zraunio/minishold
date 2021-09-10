/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:09:23 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/10 14:02:34 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	write_echo_newline_or_tab(char *echo_arg, int i)
{
	if (echo_arg[i + 1] == 'n' || echo_arg[i + 2] == 'n')
		write(1, "\n", 1);
	else if (echo_arg[i + 1] == 't' || echo_arg[i + 2] == 't')
		write(1, "\t", 1);
	if (echo_arg[i + 1] == '\\' && (echo_arg[i + 2] == 'n'
			|| echo_arg[i + 2] == 't'))
		i++;
	i += 2;
	return (i);
}

int	write_echo_slash_output(char *echo_arg, int i, int in_or_out)
{
	if (in_or_out == 2 && (echo_arg[i + 1] == 'n'
			|| (echo_arg[i + 1] == '\\' && echo_arg[i + 2] == 'n')
			|| echo_arg[i + 1] == 't' || (echo_arg[i + 1] == '\\'
				&& echo_arg[i + 2] == 't')))
		return (write_echo_newline_or_tab(echo_arg, i));
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
	else
	{
		i++;
		write(1, &echo_arg[i++], 1);
	}
	return (i);
}

void	write_echo_output(char *echo_arg, int output_len, int in_or_out,
	int quote)
{
	int	i;

	i = 0;
	while (echo_arg[i] != '\0' && i < output_len)
	{
		while (echo_arg[i] == '\\')
			i = write_echo_slash_output(echo_arg, i, in_or_out);
		if ((echo_arg[i] == '"' && (quote == 2 || quote == 0))
			|| (echo_arg[i] == '\'' && (quote == 1 || quote == 0))
			|| echo_arg[i] == '\0')
			break ;
		write(1, &echo_arg[i++], 1);
	}
}
