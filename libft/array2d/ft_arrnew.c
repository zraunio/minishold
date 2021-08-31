/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:07:37 by zraunio           #+#    #+#             */
/*   Updated: 2021/08/31 16:09:03 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

char	**ft_arrnew(size_t rows, size_t len)
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * (rows + 1));
	if (arr == NULL)
		exit (1);
	arr[0] = (char *)malloc(sizeof(char) * (len + 1));
	if (arr[0] == NULL)
		exit(1);
	return (arr);
}
