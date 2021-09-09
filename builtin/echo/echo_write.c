/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 10:48:16 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/09 10:48:28 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_newline(char *out, int i)
{
	if (out[i + 1] == 'n' || out[i + 2] == 'n')
		write(1, "\n", 1);
	else if (out[i + 1] == 't' || out[i + 2] == 't')
		write(1, "\t", 1);
	if (out[i + 1] == '\\' && (out[i + 2] == 'n'
			|| out[i + 2] == 't'))
		i++;
	i += 2;
	return (i);
}

int	handle_slash(char *out, int i, int in_or_out)
{
	if (in_or_out == 2 && (out[i + 1] == 'n'
			|| (out[i + 1] == '\\' && out[i + 2] == 'n')
			|| out[i + 1] == 't' || (out[i + 1] == '\\'
				&& out[i + 2] == 't')))
		return (handle_newline(out, i));
	else if (in_or_out == 0)
	{
		if (out[i + 1] == '\\' && (out[i + 2] == 'n'
				|| out[i + 2] == 't'))
		{
			if (out[i + 2] == 'n')
				write(1, "\n", 1);
			else if (out[i + 2] == 't')
				write(1, "\t", 1);
			i += 3;
		}
	}
	else if (in_or_out == 2)
	{
		i++;
		if (out[i + 1] == ' ')
			write(1, &out[i++], 1);
	}
	return (i);
}

void	echo_write(char *out, int output_len, int in_or_out,
	int quote)
{
	int	i;

	i = 0;
	while (out[i] != '\0' && i < output_len)
	{
		while (out[i] == '\\')
			i = handle_slash(out, i, in_or_out);
		if ((out[i] == '"' && (quote == 2 || quote == 0))
			|| (out[i] == '\'' && (quote == 1 || quote == 0))
			|| out[i] == '\0')
			break ;
		write(1, &out[i++], 1);
	}
}
