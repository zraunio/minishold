/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:41:42 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/05 16:44:35 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**split_input_to_array(char *buf)
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
	while (buf[i] == ' ')
		i++;
	while (buf[i] != '\0')
	{
		buf_arr[y][x++] = buf[i++];
		if (buf[i] == ';')
		{
			if (buf[i + 1] == ';' || buf[i + 1] == '|')
			{
				ft_printf("zsh: parse error near %.2s\n", buf + i);
				x = 0;
				while (x <= y)
					free(buf_arr[x++]);
				free(buf_arr);
				return (NULL);
			}
			if (buf[i + 1] == '\0')
				continue ;
			else
			{
				buf_arr[y++][x] = '\0';
				buf_arr[y] = (char *)malloc(sizeof(char) * 50);
				buf_arr[y++][0] = buf[i++]; 
				x = 0;
				buf_arr[y] = (char *)malloc(sizeof(char) * 50);
			}
		}
		else if (buf[i] == '|')
		{
			if (buf[i + 1] == ';' || buf[i + 1] == '|')
			{
				ft_printf("zsh: parse error near %.2s\n", buf + i);
				x = 0;
				while (x <= y)
					free(buf_arr[x++]);
				free(buf_arr);
				return (NULL);
			}
		}
	}
	buf_arr[y++][x] = '\0';
	buf_arr[y] = NULL;
	return (buf_arr);
}