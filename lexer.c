/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:41:42 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/20 16:02:49 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	pipe_input(char *buf, char **buf_arr, int x, int y)
{
	if (buf[1] == ';' || buf[1] == '|')
	{
		ft_printf("zsh: parse error near %.2s\n", buf);
		x = 0;
		while (x <= y)
			free(buf_arr[x++]);
		free(buf_arr);
		return (-1);
	}
	return (1);
}

/*
** If next character after ';' is either ';' or '|', it is considered
** parse error, we output error message, free the buf_arr and we return.
** If there is anything else, we change row, malloc space, we put that 
**
*/

int	semicolon_input(char *buf, char **buf_arr, int x, int y)
{
	if (buf[1] == ';' || buf[1] == '|')
	{
		ft_printf("zsh: parse error near %.2s\n", buf);
		x = 0;
		while (x <= y)
			free(buf_arr[x++]);
		free(buf_arr);
		return (-1);
	}
	if (buf[1] != '\0')
	{
		buf_arr[y++][x] = '\0';
		buf_arr[y] = (char *)malloc(sizeof(char) * 2);
		buf_arr[y][0] = *buf++;
		buf_arr[y++][1] = '\0';
		x = 0;
		buf_arr[y] = (char *)malloc(sizeof(char) * 50);
	}
	return (1);
}

/*
** We have input, that has been read to char *buf.
** Here we split that *buf to an array. First we skip
** spaces. When we encounter either '|' or ';', we go
** check what comes after that character to
** different functions. 
*/

char	**split_input_to_array(char *buf)
{
	char	**buf_arr;
	int		i;
	int		y;
	int		x;

	buf_arr = (char **)malloc(sizeof(char *) * 3);
	if (buf_arr == NULL)
		exit(1);
	i = 0;
	y = 0;
	x = 0;
	buf_arr[y] = (char *)malloc(sizeof(char) * 500);
	while (buf[i] == ' ')
		i++;
	while (buf[i] != '\0')
	{
		if (buf[i] == ';')
		{
			if (semicolon_input(buf + i, buf_arr, x, y) == -1)
				return (NULL);
		}
		else if (buf[i] == '|')
		{
			if (pipe_input(buf + i, buf_arr, x, y) == -1)
				return (NULL);
		}
		buf_arr[y][x++] = buf[i++];
	}
	buf_arr[y++][x] = '\0';
	buf_arr[y] = NULL;
	return (buf_arr);
}
