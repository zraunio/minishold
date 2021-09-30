/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:27:40 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/30 11:58:14 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setenv.h"

/*
** Library setenv function:
**    int setenv(const char *name, const char *value, int overwrite);
**
** In this function we check if we get 1. name of environ variable,
** 2. value for the variable and 3. int to see if we want to change 
** variable value or not, depending on the fact if it already exists
** or not (and if the int we get is either 0 or nonzero).
*/

void	ft_setenv(t_shell *data, char *args)
{
	long long	i;
	char	*variable;
	char	*value;

	args += 6;
	variable = return_string_before_given_char(++args, ' ');
	if (variable == NULL)
		return ;
	if (ft_strchr(variable, '=') != NULL)
		return (free(variable));
	args += (int)ft_strlen(variable) + 1;
	value = ft_strdup_chr(args, ' ');
	if (value == NULL)
		value = ft_strdup(args);
	else
		args = check_setenv_int(args, variable, value);
	if (args == NULL)
		return ;
	i = check_if_array(variable, data->environ);
	if (i == -1)
		return (env_new_arr(data, variable, value));
	else if (args[0] != '0')
		return (env_var_change(data, variable, value, i));
	free_two((void *)variable, (void *)value);
}
