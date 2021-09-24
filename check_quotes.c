/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:02:06 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/24 22:37:00 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_quotes_with_semicolon(char *str, int len)
{
	int		quotes;
	char	c;
	int		i;

	quotes = 0;
	i = 0;
	c = 'a';
	while (i < len)
	{
		if ((i > 0 && (str[i] == '\"' || str[i] == '\'') && str[i - 1] != '\\')
			|| (i == 0 && (str[i] == '"' || str[i] == '\'')))
		{
			c = str[i];
			quotes++;
			while (str[i] != c && i < len)
				i++;
			if (i == len)
				return (quotes);
			else if (str[i] == c)
				c = 'a';
		}
		i++;
	}	
	return (quotes);
}

char	check_quotes_for_input(char *buf, int i)
{
	char	quote;

	quote = 'a';
	while (buf[i] != '\0')
	{
		if ((i > 0 && (buf[i] == '"' || buf[i] == '\'') && buf[i - 1] != '\\')
			|| (i == 0 && (buf[i] == '"' || buf[i] == '\'')))
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
		quote = check_quotes_for_input(buf, 0);
	}
	ft_memdel((void *)&extra_buf);
}
