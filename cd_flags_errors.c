/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_flags_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 14:49:59 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/11 14:50:46 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	cd_flags_error(char *args, t_shell *data)
{
	ft_printf("cd: string not in pwd: ");
	write(1, args, data->i + 1);
	data->i = 0;
	write(1, "\n", 1);
	return (-1);
}

/*
** i marks the place we were after while loop. X is in the beginning zero.
** If args points to space, we loop through spaces (because it is fine to have
** multiple spaces in the end of cd argument). If after spaces we are at '\0',
** everything's fine and we return 1. Otherwise our argument is kind of ruined,
** and we are gonna output error message and return -1.
*/

int	check_cd_last_space(char *args, t_shell *data)
{
	while (args[data->i + data->x] == ' ' && args[data->i + data->x] != '\0')
		data->x++;
	if (args[data->i + data->x] == '\0')
		return (1);
	else
	{
		ft_printf("cd: string not in pwd: ");
		write(1, args + (data->i - data->len_of_dir), data->len_of_dir);
		write(1, "\n", 1);
		return (-1);
	}	
}
