/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 09:10:50 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/30 11:28:27 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


long long	check_if_array(char *var, char **env)
{
	long long	i;

	change_to_uppercase(var);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strstr(env[i], var) != NULL)
		{
			if (env[i][(int)ft_strlen(var)] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}
