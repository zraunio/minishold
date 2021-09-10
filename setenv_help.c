/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:06:21 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/10 17:06:44 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_if_var_is_in_array(char *variable, char **environ)
{
	int	i;

	change_to_uppercase(variable);
	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strstr(environ[i], variable) != NULL)
		{
			if (environ[i][(int)ft_strlen(variable)] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

char	*check_setenv_int(char *args, char *variable, char *value)
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
			free_two((void *)variable, (void *)value);
			return (NULL);
		}
	}
	return (args);
}
