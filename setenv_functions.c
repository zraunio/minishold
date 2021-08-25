/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 18:12:01 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/25 19:01:43 by ehelmine         ###   ########.fr       */
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

void	change_old_var_value(t_shell *data, char *var, char *value,
		int i)
{
	int		ii;
	int		x;

	if (ft_strcmp(value, "NULL") == 0)
	{
		free(value);
		free(var);
		return (remove_one_string_in_array(data->copy_of_environ, i));
	}
	free(data->copy_of_environ[i]);
	data->copy_of_environ[i] = ft_strnew((size_t)ft_strlen(var)
		+ (size_t)ft_strlen(value) + 1 + 1);
	ii = 0;
	x = 0;
	while (var[ii] != '\0')
		data->copy_of_environ[i][x++] = var[ii++];
	data->copy_of_environ[i][x++] = '=';
	ii = 0;
	while (value[ii] != '\0')
		data->copy_of_environ[i][x++] = value[ii++];
	data->copy_of_environ[i][x] = '\0';
	free(value);
	free(var);
}

char	**new_arr_with_extra_line(char **old_arr, int rows)
{
	char	**new_arr;
	int		y;

	new_arr = (char **)malloc(sizeof(char *) * (rows + 1));
	y = 0;
	while (old_arr[y] != NULL)
	{
		new_arr[y] = ft_strdup(old_arr[y]);
		free(old_arr[y++]);
	}
	free(old_arr);
	return (new_arr);
}

/*
**
**
*/

void	add_new_var_to_environ(t_shell *data, char *var, char *value)
{
	int	y;
	int	x;
	int	i;
	int	len;
	char **new_arr;

	y = data->num_of_variables + 1;
	new_arr = new_arr_with_extra_line(data->copy_of_environ, y);
	len = (int)ft_strlen(var) + (int)ft_strlen(value) + 1;
	new_arr[--y] = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	x = 0;
	while (var[i] != '\0')
		new_arr[y][x++] = var[i++];
	new_arr[y][x++] = '=';
	i = 0;
	while (value[i] != '\0')
		new_arr[y][x++] = value[i++];
	new_arr[y++][x] = '\0';
	new_arr[y] = NULL;
	data->num_of_variables = y;
	data->copy_of_environ = ft_arrdup(new_arr);
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
** Library setenv function:
**    int setenv(const char *name, const char *value, int overwrite);
**
** In this function we check if we get 1. name of environ variable,
** 2. value for the variable and 3. int to see if we want to change 
** variable value or not, depending on the fact if it already exists
** or not (and if the int we get is either 0 or nonzero).
*/

void	set_environment_variable(t_shell *data, char *args)
{
	int		var_index;
	char	*variable;
	char	*value;
	int		change_flag;

	args += 7;
	change_flag = 1;
	if (args[0] == '\0')
		return (ft_putarr(data->copy_of_environ));
	variable = return_string_before_given_character(args, ' ');
	if (variable == NULL)
		return ;
	if (ft_strchr(variable, '=') != NULL)
		return (free(variable));
	args += (int)ft_strlen(variable) + 1;
	value = return_string_before_given_character(args, ' ');
	if (value == NULL)
		value = ft_strdup(args);
	else
	{
		args += (int)ft_strlen(value) + 1;
//		ADD HERE SOMETHING,  THAT CHECKS, IF THE LAST GIVEN INPUT IS
//		FOR CERTAIN SOME INT (CAN BE ANYTHING BETWEEN -2147483648 AND +2147483648)
//		SO IT NEEDS TO RECOGNISE ALSO -, +, AND A LOT OF NUMBERS. NOT ONLY ONE.
//		NOW IT RECOGNISES ONLY ONE NUMBER.
		if (!ft_isdigit((int)args[0]) || (ft_isdigit((int)args[0]) && args[1] != '\0'))
			return (free_two((void *)variable, (void *)value));
	}
	var_index = check_if_var_is_in_array(variable, data->copy_of_environ);
	if (var_index == -1)
		return (add_new_var_to_environ(data, variable, value));
	else if (var_index != -1 && args[0] != '0')
		return (change_old_var_value(data, variable, value, var_index));
	free_two((void *)variable, (void *)value);
}