/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:31:20 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/30 11:32:27 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

char	*ft_strdup_chr(char *str, char c)
{
	size_t		i;

	i = 0;
	if (c == '\0')
		return (ft_strdup(str));
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (ft_strndup(str, i));
		i++;
	}
	exit (1);
}
