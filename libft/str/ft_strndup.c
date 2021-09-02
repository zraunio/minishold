/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 10:21:34 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/02 16:55:52 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = 0;
	while (s1[len] != '\0')
		len++;
	if (n >= len)
		n = len;
	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (dup == NULL)
		exit (1);
	i = 0;
	while (i < n)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
