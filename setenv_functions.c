/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 18:12:01 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/20 15:49:52 by ehelmine         ###   ########.fr       */
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
	args += 7;
	if (args[0] == '\0')
	{
		ft_putarr(copy_of_environ);
		return ;
	}
	variable = return_string_before_given_character(args, ' ');
	if (variable == NULL)
		variable = ft_strdup(args);
	if (args[(int)ft_strlen(variable)] != '\0')
	{
		args += (int)ft_strlen(variable);
		args++;
		i = 0;
		while (args[i] != '\0')
			i++;
		value = ft_strndup(args, i);
		ft_printf("variable: %s & value: %s\n", variable, value);
		free(value);
	}
	free(variable);
}