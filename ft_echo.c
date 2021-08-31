/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 09:44:25 by zraunio           #+#    #+#             */
/*   Updated: 2021/08/27 10:08:55 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*dollar_write(char *out, char **env)
{
	size_t	i;
	size_t	j;
	char	*tmp;
	char	*cmp;

	i = 0;
	if (ft_isspace(out[i]) == 1)
		return (out);
	while (ft_isspace(out[i]) == 0 && out[i] != '"' && out[i] != '\0')
		i++;
	tmp = ft_strsub(out, 0, i);
	i = 0;
	while (tmp[i++])
		if (tmp[i] >= 97 || tmp[i] <= 122)
			tmp[i] = ft_toupper(tmp[i]);
	i = 0;
	j = ft_strlen(tmp);
	while (**env != NULL)
	{
		
	}
}

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
