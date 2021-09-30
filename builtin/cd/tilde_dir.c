/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:16:11 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/30 11:16:54 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

char	*tilde_dir(char *dir_name, t_shell *data)
{
	int		i;
	char	*new_dir;
	char	*home;
	char	*end;

	i = check_if_var_is_in_array("HOME", data->environ);
	if (i == -1)
		return (NULL);
	home = ft_strstr_after(data->environ[i], "HOME=");
	if (ft_strequ(dir_name, "~"))
		return (ft_strdup(home));
	else
	{
		end = ft_strdup(dir_name + 1);
		new_dir = ft_strjoin(home, end);
		ft_memdel((void *)&end);
		return (new_dir);
	}
	return (NULL);
}
