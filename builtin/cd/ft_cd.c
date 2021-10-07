/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:44:41 by zraunio           #+#    #+#             */
/*   Updated: 2021/10/07 11:04:11 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

/*
** Returns the dir where we want to enter depending on what was given as input.
**
*/

static char	*cd_get_next_dir_2(t_shell *data, char *dir_name)
{
	char	*new_dir;
	int		i;

	if (ft_strequ(dir_name, "-"))
	{
		i = check_if_var_is_in_array("OLDPWD", data->environ);
		if (i == -1)
			return (NULL);
		new_dir = ft_strstr_after(data->environ[i], "OLDPWD=");
		data->cd_previous_dir = 1;
		return (ft_strdup(new_dir));
	}
	else
		return (ft_strdup(dir_name));
}

static char	*cd_get_next_dir(t_shell *data, char *dir_name, char *curr_dir)
{
	char	*new_dir;
	int		i;

	if (dir_name == NULL)
	{
		i = check_if_var_is_in_array("HOME", data->environ);
		if (i == -1)
			return (NULL);
		new_dir = ft_strstr_after(data->environ[i], "HOME=");
		return (ft_strdup(new_dir));
	}
	else if (ft_strequ(dir_name, "~") || dir_name[0] == '~')
		return (tilde_dir_name(dir_name, data));
	else if (ft_strequ(dir_name, ".") || ft_strequ(dir_name, ""))
		return (ft_strdup(curr_dir));
	else if (ft_strequ(dir_name, ".."))
	{
		i = ft_return_char_index(curr_dir, '/', 'e');
		if (i == 0)
			return (ft_strdup("/"));
		new_dir = ft_strndup(curr_dir, i);
		return (new_dir);
	}
	return (cd_get_next_dir_2(data, dir_name));
}

/*
** First we args++ 2 to skip 'cd' word. Then we go to check_cd_arguments
** function, that checks how the input arguments for cd look like. If it
** returns -1, it means there's something wrong with the arguments. That
** function outputs error message, so here we only want to go back.
** If check_cd_arguments returns something else, we want to continue.
** Now we call ft_strsplit to get all args in array.
** We work with arr[0] (thats why i = 0). If either of the flags are 1,
** we define i = 1 so we work with different row.
*/

void	ft_cd(char *args, t_shell *data, size_t i)
{
	char	**arr;
	char	*curr_dir;
	char	*new_dir;

	if (cd_args_check(args, data) == -1)
		return ;
	arr = ft_strsplit(args, ' ');
	check_if_null_arr((void **)arr);
	while (arr[i] != NULL)
	{
		if (arr[i][0] != '-' || (arr[i][0] == '-' && arr[i][1] == '\0'))
			break ;
		i++;
	}
	curr_dir = get_current_dir();
	if (curr_dir == NULL)
		return (free_arr((void *)&arr));
	dir_compare(curr_dir, data);
	quotes_trim(arr[i]);
	new_dir = cd_get_next_dir(data, arr[i], curr_dir);
	if (new_dir != NULL)
		cd_into_dir(curr_dir, new_dir, data, arr[i]);
	else
		ft_memdel((void *)&curr_dir);
	free_arr((void *)&arr);
}
