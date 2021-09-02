/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 09:44:25 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/02 16:47:41 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char *str, char **env)
{
	char	*out;
	size_t	i;

	i = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	out = ft_strstr(&out[i], " ");
	if (out != NULL)
	{
		i = 0;
		while (ft_isspace(out[i]) == 1)
			i++;
		if (out[i] == '$')
		{
			out = dollar_write(&out[i + 1], env);
			i = 0;
		}
/*
** rewrite of the echo command:
** handles Dollar $, quotes, and ~
*/
	}
	write(1, "\n", 1);
	return ;
}
