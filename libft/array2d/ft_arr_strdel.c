/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_strdel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:41:50 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/30 11:42:41 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	ft_arr_strdel(char **array, int row)
{
	while (array[row + 1] != NULL)
	{
		ft_memdel((void *)&array[row]);
		array[row] = ft_strnew((int)ft_strlen(array[row + 1]));
		ft_strcpy(array[row], array[row + 1]);
		row++;
	}
	free(array[row]);
	array[row] = NULL;
}
