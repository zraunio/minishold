/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:52:29 by zraunio           #+#    #+#             */
/*   Updated: 2021/08/31 16:42:28 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	path_write(char *tmp, char *env)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(tmp);
	i = 0;
	free(tmp);
	tmp = ft_strdup(*env + (len + 1));
	while (tmp[i] != '\0')
	{
		if (tmp[i] == ':')
			tmp[i] = ' ';
		i++;
	}
	ft_putstr(tmp);
}

char	*dollar_write(char *out, char **env)
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
	j = ft_strlen(tmp);
	while (**env != NULL)
	{
		cmp = ft_strstr(*env, tmp);
		if (cmp != NULL)
		{
			if (ft_strcmp(tmp, "PATH") == 0)
				path_write(tmp, *env);
			else
				ft_putstr(tmp);
		}
		else
		{
			/* code */
		}
		
	}
}
