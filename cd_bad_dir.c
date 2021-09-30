/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bad_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:53:53 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/30 16:29:56 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*cd_bad_dir(char *tmp, char *cur, t_shell *data)
{
	int		i;

	i = 1;
	if (ft_strequ(tmp, "..") || ft_strequ(tmp, ".") || ft_strequ(tmp, "~")
		|| ft_strequ(tmp, "../") || ft_strequ(tmp, "/"))
		return (ft_strdup(tmp));
	while (tmp[i] != '\0')
	{
		while (tmp[i] != '\0' && (tmp[i] == '.' || tmp[i] == '/'))
			i++;
		if (tmp[i] == '\0')
		{
			if (tmp[0] == '/')
				return (ft_strdup("/"));
			break ;
		}
		return (ft_strdup(tmp));
	}
	free_two((void *)&cur, (void *)&data->prev_dir);
	return (NULL);
}
