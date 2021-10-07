/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:15:24 by zraunio           #+#    #+#             */
/*   Updated: 2021/10/07 10:34:57 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	free_arr(void ***arr)
{
	size_t	i;

	i = 0;
	if (*arr != NULL)
	{
		while ((*arr)[i] != NULL)
			ft_memdel((void **)&(*arr)[i++]);
		free(*arr);
	}
	*arr = NULL;
}
