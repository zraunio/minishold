/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dir_rights.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 13:03:36 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/16 13:22:20 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_dir_rights(char *new_dir, char *current_dir, t_shell *data,
	char *org_input)
{
	struct stat	b;
	int			i;

	i = lstat(new_dir, &b);
	if (i == -1)
		return (1);
	if (i == 0 && b.st_mode & S_IXUSR)
		return (1);
	else
	{
		ft_printf("cd: permission denied: %s\n", org_input);
		free_two((void *)new_dir, (void *)current_dir);
		if (data->prev_dir != NULL)
		{
			free(data->prev_dir);
			data->prev_dir = NULL;
		}
		return (-1);
	}
}
