/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:45:48 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/30 12:07:21 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/setenv.h"

char	*env_check_int(char *args, char *var, char *value)
{
	int	i;

	args += (int)ft_strlen(value) + 1;
	i = 0;
	if (args[i] == '-' && args[i + 1] != '\0' && ft_isdigit(args[i + 1]))
		i++;
	while (args[i] != '\0' && ft_isdigit(args[i]))
		i++;
	if (args[i] != '\0')
	{
		while (args[i] != '\0' && ft_isspace(args[i]))
			i++;
		if (args[i] != '\0')
		{
			free_two((void *)var, (void *)value);
			return (NULL);
		}
	}
	return (args);
}
