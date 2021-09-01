/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:52:29 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/01 15:57:56 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	path_write(char *tmp, char *env)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(tmp);
	i = 0;
	ft_memdel(tmp);
	tmp = ft_strdup(&env[len + 1]);
	while (tmp[i] != '\0')
	{
		if (tmp[i] == ':')
			tmp[i] = ' ';
		i++;
	}
	ft_putstr(tmp);
}

static char *find_start(char *out)
{
	size_t	i;
	char *tmp;

	i = 0;
	if (ft_isspace(out[i]) == 1)
		return (out);
	while (ft_isspace(out[i]) == 0 && out[i] != '"' && out[i] != '\0')
		i++;
	tmp = ft_strsub(out, 0, i);
	if (!tmp)
	{
		write (1, "find_start", 11);
		exit (1);
	}
	i = 0;
	while (tmp[i++])
		if (tmp[i] >= 97 || tmp[i] <= 122)
			tmp[i] = ft_toupper(tmp[i]);
	return (tmp);
}

char	*dollar_write(char *out, char **env)
{
	size_t	i;
	size_t	j;
	char	*tmp;
	char	*cmp;

	i = 0;
	tmp = find_start;
	j = ft_strlen(tmp);
	while (env[i] != NULL)
	{
		cmp = ft_strstr(env[i], tmp);
		if (cmp != NULL)
		{
			if (ft_strcmp(tmp, "PATH") == 0)
				path_write(tmp, env[i]);
			else
				ft_putstr(&env[i][j + 1]);
			break ;
		}
		else
			i++;
	}
	ft_memdel(&tmp);
	if (out[j] == '"')
		j++;
	if (env[i] == NULL && out[j - 1] == '"')
		write(1, " ", 1);
	return (out + j);
}
