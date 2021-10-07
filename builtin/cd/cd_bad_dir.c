/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bad_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 10:05:31 by zraunio           #+#    #+#             */
/*   Updated: 2021/10/07 10:06:07 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cd.h"

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
