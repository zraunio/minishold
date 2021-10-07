/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:41:42 by ehelmine          #+#    #+#             */
/*   Updated: 2021/10/07 10:55:07 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
** If next character after '|' is either ';' or '|', it is considered
** parse error, so we output error message, free the buf_arr and we return -1.
** If there is anything else, we want to put that to same row, 'cause
** pipe separation means that these commands need to be done "together".
** And that's why we return 1, 'cause we just continue inside the while loop.
*/

static int	pipe_input(char *buf, char **buf_arr, int x, int y)
{
	if (buf[1] == ';' || buf[1] == '|')
	{
		ft_printf("minishell: parse error near `%.2s'\n", buf);
		x = 0;
		while (x <= y)
			ft_memdel((void *)&buf_arr[x++]);
		free(buf_arr);
		return (-1);
	}
	return (1);
}

/*
** If next character after ';' is either ';' or '|', it is considered
** parse error, we output error message, free the buf_arr and we return -1.
** If there is anything else, we want to get that to the array.
** ';' tells us, that we want to put things separately (different
** commands).
** And that's why now we change row, malloc space, we put that 
** ';' to own row, then we again change row and malloc space for
** next row and go back returning 1.
*/

static int	semicolon_input(char *buf, char **buf_arr, int x, int y)
{
	if (buf[1] == ';' || buf[1] == '|')
	{
		ft_printf("minishell: parse error near `%.2s'\n", buf);
		x = 0;
		while (x <= y)
			ft_memdel((void *)&buf_arr[x++]);
		free(buf_arr);
		return (-1);
	}
	if (buf[1] != '\0')
	{
		buf_arr[y++][x] = '\0';
		buf_arr[y] = (char *)malloc(sizeof(char) * 2);
		if (buf_arr[y] == NULL)
			exit (1);
		buf_arr[y][0] = *buf++;
		buf_arr[y++][1] = '\0';
		buf_arr[y] = (char *)malloc(sizeof(char) * 500);
		if (buf_arr[y] == NULL)
			exit (1);
	}
	return (y);
}

/*
** When we have found semicolon, we first check if there is echo involved.
** So we check 1. amount of quotes, and if there is zero quotes or there
** is quotes as pairs (%2 == 0), then we return -1, as we know then
** we want to split the input (maybe new command after ;).
** If there's more than zero and quotes % 2 != 0, we check if we have 
** echo in the command. If there is, we want to keep ';' character inside
** the line we give to echo (for example echo "hello world ; continue").
** If we want to split, return -1 and if we don't want to, return 1.
*/

int	check_if_echo(char *str, int len)
{
	int	quotes;

	quotes = check_quotes_with_semicolon(str, len, 0);
	if (str[0] == 'e' && str[1] == 'c' && str[2] == 'h' && str[3] == 'o'
		&& ft_isspace(str[4]))
	{
		if (quotes != 0)
			return (1);
		return (-1);
	}
	else if ((str[0] == '\'' && str[5] == '\'') || (str[0] == '\"' && str[5]
			== '\"'))
	{
		if (str[1] == 'e' && str[2] == 'c' && str[3] == 'h' && str[4] == 'o'
			&& ft_isspace(str[6]))
		{
			if (quotes != 0)
				return (1);
			return (-1);
		}
	}
	else if (quotes != 0)
		return (1);
	return (-1);
}

static char	**input_to_array_loop(char *buf, int i, char **buf_arr,
	int in[2])
{
	while (buf[i] != '\0')
	{
		if (buf[i] == ';')
		{
			if (check_if_echo(buf_arr[in[0]], in[1]) == -1)
			{
				in[0] = semicolon_input(buf + i++, buf_arr, in[1], in[0]);
				if (in[0] == -1)
					return (NULL);
				if (buf[i] == '\0')
					break ;
				in[1] = 0;
				while (ft_isspace(buf[i]) == ' ' && buf[i] != '\0')
					i++;
			}
		}
		else if (buf[i] == '|')
			if (pipe_input(buf + i, buf_arr, in[1], in[0]) == -1)
				return (NULL);
		buf_arr[in[0]][in[1]++] = buf[i++];
	}
	buf_arr[in[0]++][in[1]] = '\0';
	buf_arr[in[0]] = NULL;
	return (buf_arr);
}

/*
** We have input, that has been read to char *buf.
** Here we split that *buf to an array. First we skip
** spaces. When we encounter either '|' or ';', we go
** check what comes after that character to
** different functions. 
*/

char	**split_input_to_array(char *buf, int i)
{
	char	**buf_arr;
	int		index[2];

	buf_arr = ft_arrnew(500, 500);
	while (ft_isspace(buf[i]) && buf[i] != '\0')
		i++;
	index[0] = 0;
	index[1] = 0;
	return (input_to_array_loop(buf, i, buf_arr, index));
}
