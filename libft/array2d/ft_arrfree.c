/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:15:24 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/30 10:58:52 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	ft_arr_free(char ***arr)
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
