/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:14:39 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/30 15:30:10 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
		data->previous_dir_in_cd = 1;
		return (ft_strdup(new_dir));
	}
	else
		return (ft_strdup(dir_name));
}

static char	*cd_get_next_dir(t_shell *data, char *dir_name, char *current_dir)
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
		return (ft_strdup(current_dir));
	else if (ft_strequ(dir_name, ".."))
	{
		i = ft_return_char_index(current_dir, '/', 'e');
		if (i == 0)
			return (ft_strdup("/"));
		new_dir = ft_strndup(current_dir, i);
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

void	cd_function_start(char *args, t_shell *data, int i)
{
	char	**ag_ar;
	char	*current_dir;
	char	*new_dir;

	if (check_cd_arguments(args, data) == -1)
		return ;
	ag_ar = ft_strsplit(args, ' ');
	check_if_null_arr((void **)ag_ar);
	while (ag_ar[i] != NULL)
	{
		if (ag_ar[i][0] != '-' || (ag_ar[i][0] == '-' && ag_ar[i][1] == '\0'))
			break ;
		i++;
	}
	current_dir = get_current_dir();
	if (current_dir == NULL)
		return (free_arr((void *)&ag_ar));
	compare_current_dir_to_prev(current_dir, data);
	clean_quotes_from_dir_name(ag_ar[i]);
	new_dir = cd_get_next_dir(data, ag_ar[i], current_dir);
	if (new_dir != NULL)
		cd_function_finish(current_dir, new_dir, data, ag_ar[i]);
	else
		ft_memdel((void *)&current_dir);
	free_arr((void *)&ag_ar);
}
