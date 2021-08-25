/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 17:25:57 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/24 18:19:32 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
**
**
*/

void	unset_environment_variable(char **copy_of_environ, char *args)
{
	int var_index;
	char *variable;

	args += 9;
	if (args[0] == '\0')
		return ;
	variable = ft_strdup(args);
	var_index = check_if_var_is_in_array(variable, copy_of_environ);
	if (var_index != -1)
		remove_one_string_in_array(copy_of_environ, var_index);
	free(variable);
	return ;
}
