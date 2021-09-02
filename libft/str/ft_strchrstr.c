/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:39:56 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/02 17:07:11 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"
#include <stdio.h>

int		ft_strchrstr(char *str, char c, char start)
{
	size_t	i;

	i = 0;
	if (start == 'b')
	{
		while (str[i] != '\0')
		{
			if (str[i] == c)
				return (i);
			i++;
		}
	}
	else if (start == 'e')
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
