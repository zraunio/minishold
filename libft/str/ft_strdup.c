/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 12:37:55 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/30 11:21:48 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

char	*ft_strdup(const char *src)
{
	char		*str;
	size_t		i;

	i = 0;
	str = (char *)malloc(sizeof(*str) * (ft_strlen(src) + 1));
	if (!str)
		exit (1);
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	if (!src)
		exit (1);
	return (str);
}
