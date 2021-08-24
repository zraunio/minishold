/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 18:12:01 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/24 18:16:41 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
** 
**
*/

/*
**
**
**
*/

void	change_old_var_value(char **copy_of_environ, char *var, char *value,
		int i)
{
	int x;
	int ii;

	if (ft_strcmp(value, "NULL") == 0)
	{
		free(value);
		free(var);
		return (remove_one_string_in_array(copy_of_environ, i));
	}
	x = (int)ft_strlen(var) + 1;
	ii = 0;
	while (value[ii] != '\0')
		copy_of_environ[i][x++] = value[ii++];
	copy_of_environ[i][x] = '\0';
	free(value);
	free(var);
}

/*
**
**
*/

void	add_new_var_to_environ(char **copy_of_environ, char *var, char *value)
{
	int y;
	int x;
	int i;

	y = 0;
	while (copy_of_environ[y] != NULL)
		y++;
	copy_of_environ[y] = (char *)malloc(sizeof(char) * 500);
	i = 0;
	x = 0;
	while (var[i] != '\0')
		copy_of_environ[y][x++] = var[i++];
	copy_of_environ[y][x++] = '=';
	i = 0;
	while (value[i] != '\0')
		copy_of_environ[y][x++] = value[i++];
	copy_of_environ[y++][x] = '\0';
	copy_of_environ[y] = NULL;
	free(value);
	free(var);
}

/*
**
**
**
*/

int	check_if_var_is_in_array(char *variable, char **copy_of_environ)
{
	int i;

	change_to_uppercase(variable);
	i = 0;
	while (copy_of_environ[i] != NULL)
	{
		if (ft_strstr(copy_of_environ[i], variable) != NULL)
		{
			if (copy_of_environ[i][(int)ft_strlen(variable)] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

/*
**
**
**
*/

void	set_environment_variable(char **copy_of_environ, char *args)
{
	int		var_index;
	char	*variable;
	char	*value;
	int		change_flag;

	args += 7;
	change_flag = 1;
	if (args[0] == '\0')
		return (ft_putarr(copy_of_environ));
	variable = return_string_before_given_character(args, ' ');
	if (variable == NULL)
		return (ft_putstr("env value missing\n"));
	if (ft_strchr(variable, '=') != NULL)
	{
		free(variable);
		return (ft_putstr("invalid var name containing '='\n"));
	}
	args += (int)ft_strlen(variable) + 1;
	value = return_string_before_given_character(args, ' ');
	if (value == NULL)
		value = ft_strdup(args);
	else
	{
		args += (int)ft_strlen(value) + 1;
		if (!ft_isdigit((int)args[0]) || (ft_isdigit((int)args[0]) && args[1] != '\0'))
		{
			free(variable);
			free(value);
			return (ft_putstr("invalid change flag\n"));
		}
	}
	var_index = check_if_var_is_in_array(variable, copy_of_environ);
	if (var_index == -1)
		return (add_new_var_to_environ(copy_of_environ, variable, value));
	else if (var_index != -1 && args[0] != '0')
		return (change_old_var_value(copy_of_environ, variable, value, var_index));
	free(variable);
	free(value);
	return ;
}