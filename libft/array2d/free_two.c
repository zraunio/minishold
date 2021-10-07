/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:23:20 by ehelmine          #+#    #+#             */
/*   Updated: 2021/10/07 10:37:01 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	free_two(void **ptr1, void **ptr2)
{
	if (*ptr1 != NULL)
	{
		free(*ptr1);
		*ptr1 = NULL;
	}
	if (*ptr2 != NULL)
	{
		free(*ptr2);
		*ptr2 = NULL;
	}
}
