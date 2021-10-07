/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_change.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:56:16 by zraunio           #+#    #+#             */
/*   Updated: 2021/10/07 10:57:53 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/setenv.h"

void	env_var_change(t_shell *data, char *var, char *val, int i)
{
	size_t	ii;
	size_t	x;

	if (ft_strcmp(val, "NULL") == 0)
	{
		free_two((void *)val, (void *)var);
		return (remove_one_string_in_array(data->environ, i));
	}
	ft_memdel((void *)&data->environ[i]);
	data->environ[i] = ft_strnew(ft_strlen(var)
			+ ft_strlen(val) + 1 + 1);
	ii = 0;
	x = 0;
	while (var[ii] != '\0')
		data->environ[i][x++] = var[ii++];
	data->environ[i][x++] = '=';
	ii = 0;
	while (val[ii] != '\0')
		data->environ[i][x++] = val[ii++];
	data->environ[i][x] = '\0';
	free_two((void *)val, (void *)var);
}
