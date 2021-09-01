/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 08:54:50 by zraunio           #+#    #+#             */
/*   Updated: 2021/05/18 15:00:20 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*dest;

	if (ptr && size == 0)
	{
		dest = (void *)malloc(1);
		if (!dest)
			return (NULL);
		ft_memdel(ptr);
		return (dest);
	}
	dest = (void *)malloc(size);
	if (!dest)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(dest, ptr, size);
		ft_memdel(ptr);
	}
	return ((void *)dest);
}
