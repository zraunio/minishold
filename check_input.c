/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 16:53:11 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/02 16:54:54 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	change_input_row(char **buf_arr, int y, int x, char quote)
{
	int		start;
	char	*begin;
	char	*middle;
	char	*end;
	char	*tmp;

	start = x;
	while (buf_arr[y][x] != quote && buf_arr[y][x] != '\0')
		x++;
	if (start - 1 < 0)
		begin = ft_strdup("");
	else
		begin = ft_strndup(buf_arr[y], start - 1);
	if (x - start < 0)
		middle = ft_strdup("");
	else
		middle = ft_strsub(buf_arr[y], start, x - start);
	end = ft_strdup(buf_arr[y] + x + 1);
	tmp = ft_strjoin_three(begin, middle, end);
	ft_memset((void *)buf_arr[y], 0, ft_strlen(buf_arr[y]));
	ft_strcpy(buf_arr[y], tmp);
	free_two((void *)begin, (void *)middle);
	free_two((void *)end, (void *)tmp);
}

void	check_input_array(char **buf_arr)
{
	int		y;
	int		x;
	char	quote;
	
	y = 0;
	x = 0;
	quote = 'a';
	while (buf_arr[y] != NULL)
	{
		while (buf_arr[y][x] != '\0')
		{
			if (buf_arr[y][x] == '"' || buf_arr[y][x] == '\'')
			{
				quote = buf_arr[y][x++];
				change_input_row(buf_arr, y, x, quote);
				quote = 'a';
				x = -1;
			}
			x++;
		}
		y++;
		x = 0;
	}
}

char	check_quotes_for_input(char *buf)
{
	int		i;
	char	quote;

	i = 0;
	quote = 'a';
	while (buf[i] != '\0')
	{
		if (buf[i] == '"' || buf[i] == '\'')
		{
			quote = buf[i++];
			while (buf[i] != quote && buf[i] != '\0')
				i++;
			if (buf[i] == '\0')
				return (quote);
			else if (buf[i] == quote && buf[i - 1] == '\\')
				i++;
			else
				quote = 'a';
		}
		i++;
	}
	return (quote);
}

void	loop_more_quotes(char *buf, char quote)
{
	char *extra_buf;

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