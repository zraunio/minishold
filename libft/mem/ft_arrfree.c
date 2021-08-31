/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:15:24 by zraunio           #+#    #+#             */
/*   Updated: 2021/05/18 14:58:02 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	ft_arr_free(char **arr)
{
	size_t	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		if (arr[i] != NULL)
			free(arr[i]);
		i++;
	}
	free(arr);
}
