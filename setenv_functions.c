/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 18:12:01 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/23 15:05:40 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
** setenv VAR [VALUE]
**
*/
/*
void	check_if_env_variable(char *variable, char **copy_of_environ)
{
	int i;

	i = 0;
	change_to_uppercase(variable);
	while (copy_of_environ[i] != NULL)
	{
		if (ft_strstr(copy_of_environ, variable) != NULL)
		{
			
		}
	}
}
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