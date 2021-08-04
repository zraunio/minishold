/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:41:42 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/04 17:04:56 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	split_input_to_array(char *buf)
{
	char **buf_arr;
	int i;
	int y;
	int x;

	buf_arr = (char **)malloc(sizeof(char *) * 50);
	if (buf_arr == NULL)
		exit(1);
	i = 0;
	y = 0;
	x = 0;
	buf_arr[y] = (char *)malloc(sizeof(char) * 50);
	while (buf[i] != '\0')
	{
		while (buf[i] == ';')
			i++;
		buf_arr[y][x++] = buf[i++];
		if (buf[i] == ';')
		{
			if (buf[i + 1] == '\0')
				continue ;
			else
			{
				buf_arr[y][x] = '\0';
				y++;
				i++;
				x = 0;
				buf_arr[y] = (char *)malloc(sizeof(char) * 50);
			}
		}
	}
	buf_arr[y++][x] = '\0';
	buf_arr[y] = NULL;
	i = 0;
	while (buf_arr[i] != NULL)
	{
		write(1, "|", 1);
		ft_putstr(buf_arr[i++]);
		ft_putstr("|\n");
	}
}