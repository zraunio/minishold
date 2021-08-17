/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 18:12:01 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/17 18:20:28 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
** setenv VAR [VALUE]
**
*/

void	set_environment_variable(char **copy_of_environ, char *args)
{
	int		i;
	char	*variable;
	char	*value;

	i = 0;
	ft_printf("copy_of_environ example %s args %s\n", copy_of_environ[0], args);
	args += 7;
	while (args[i] != ' ')
		i++;
	variable = ft_strndup(args, i);
	if (args[i + 1] == '\0')
		ft_printf("set var: %s to null\n", variable);
	else
	{
		args += i;
		args++;
		i = 0;
		while (args[i] != '\0')
			i++;
		value = ft_strndup(args, i);
		ft_printf("value: %s\n", value);
		free(value);
	}
	free(variable);
}