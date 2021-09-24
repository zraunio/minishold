/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchar_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 09:17:02 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/22 09:27:32 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

long long	ft_strchr_index(char *str, char c, char startpoint)
{
	long long	i;

	i = 0;
	if (startpoint == 'b')
	{
		while (str[i] != '\0')
		{
			if (str[i] == c)
				return (i);
			i++;
		}
	}
	else if (startpoint == 'e')
	{
		i = ft_strlen(str);
		while (i >= 0)
		{
			if (str[i] == c)
				return (i);
			i--;
		}
	}
	return (-1);
}
