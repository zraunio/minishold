/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 17:25:57 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/08 19:06:57 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
**
**
*/

void	unset_environment_variable(t_shell *data, char *args)
{
	int		var_index;
	char	*variable;
	int		i;

	args += 8;
	variable = ft_strdup(++args);
	var_index = check_if_var_is_in_array(variable, data->environ);
	if (var_index != -1)
		remove_one_string_in_array(data->environ, var_index);
	i = 0;
	while (data->environ[i] != NULL)
		i++;
	data->num_of_variables = i;
	free(variable);
	return ;
}
