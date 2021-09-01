/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 09:44:25 by zraunio           #+#    #+#             */
/*   Updated: 2021/08/31 15:52:46 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


static char	*echo_write(char *out)
{

}

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
		else if (out[i] != '|' || out[i] != ';')
		{
			out = echo_write(&out[i]);
			i = 0;
		}
	}
	write(1, "\n", 1);
	return ;
}
