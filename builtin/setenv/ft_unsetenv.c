/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:47:55 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/30 11:52:49 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/setenv.h"

/*
** int setenv(const char *name, const char *value, int overwrite);
*/

void	ft_unsetenv(t_shell *data, char *args)
{
	long long	index;
	char		*variable;
	int			i;

	args += 8;
	variable = ft_strdup(++args);
	i = check_if_var_is_in_array(variable, data->environ);
	if (index != -1)
		remove_one_string_in_array(data->environ, index);
	i = 0;
	while (data->environ[i] != NULL)
		i++;
	data->num_of_variables = i;
	ft_memdel((void *)&variable);
	return ;
}
