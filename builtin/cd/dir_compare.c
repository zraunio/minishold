/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_compare.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:44:26 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/21 10:57:01 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

void	dir_compare(char *curr_dir, t_shell *data)
{
	if (data->prev_dir == NULL)
		return ;
	if (ft_strequ(curr_dir, data->prev_dir))
		return ;
	ft_memset((void *)curr_dir, 0, 4096);
	ft_strcpy(curr_dir, data->prev_dir);
}
