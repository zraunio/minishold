/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_new_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:38:41 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/30 11:39:39 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setenv.h"

static char	**arrnew_extra_line(char **old_arr, int rows)
{
	char	**new_arr;
	int		y;

	new_arr = (char **)malloc(sizeof(char *) * (rows + 1));
	y = 0;
	while (old_arr[y] != NULL)
	{
		new_arr[y] = ft_strdup(old_arr[y]);
		free(old_arr[y++]);
	}
	free(old_arr);
	return (new_arr);
}

void	env_new_var(t_shell *data, char *var, char *value)
{
	int		y;
	int		x;
	int		i;
	int		len;
	char	**new_arr;

	y = data->num_of_variables + 1;
	new_arr = new_arr_with_extra_line(data->environ, y);
	len = (int)ft_strlen(var) + (int)ft_strlen(value) + 1;
	new_arr[--y] = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	x = 0;
	while (var[i] != '\0')
		new_arr[y][x++] = var[i++];
	new_arr[y][x++] = '=';
	i = 0;
	while (value[i] != '\0')
		new_arr[y][x++] = value[i++];
	new_arr[y++][x] = '\0';
	new_arr[y] = NULL;
	data->num_of_variables = y;
	data->environ = ft_arrdup(new_arr);
	free_two((void *)value, (void *)var);
}
