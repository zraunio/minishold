/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:02:06 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/10 17:02:23 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	check_quotes_for_input(char *buf)
{
	int		i;
	char	quote;

	i = 0;
	quote = 'a';
	while (buf[i] != '\0')
	{
		if ((buf[i] == '"' || buf[i] == '\'') && buf[i - 1] != '\\')
		{
			quote = buf[i++];
			while (buf[i] != quote && buf[i] != '\0')
			{
				if (buf[i] == '\\' && buf[i + 1] == quote)
					i += 2;
				else
					i++;
			}
			if (buf[i] == '\0')
				return (quote);
			else if (buf[i] == quote)
				quote = 'a';
		}
		i++;
	}
	return (quote);
}

void	loop_more_quotes(char *buf, char quote)
{
	char	*extra_buf;

	extra_buf = (char *)malloc(sizeof(char) * 100);
	if (extra_buf == NULL)
		exit (1);
	while (quote != 'a')
	{
		if (quote == '"')
			write(1, "dquote> ", 8);
		else
			write(1, "quote> ", 7);
		ft_memset((void *)extra_buf, 0, 100);
		extra_buf[0] = '\n';
		loop_input_to_string(extra_buf + 1);
		ft_strcat(buf, extra_buf);
		quote = check_quotes_for_input(buf);
	}
	free(extra_buf);
}
