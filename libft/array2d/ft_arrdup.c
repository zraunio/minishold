/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:04:12 by zraunio           #+#    #+#             */
/*   Updated: 2021/08/31 16:05:51 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

char	**ft_arrdup(char **arr)
{
	int		j;
	int		i;
	char	**arr_new;

	j = 0;
	while (arr[j] != NULL)
		j++;
	arr_new = (char **)malloc(sizeof(char *) * (j + 1));
	if (arr_new == NULL)
		exit (1);
	i = 0;
	while (arr[i] != NULL)
	{
		arr_new[i] = ft_strdup(arr[i]);
		if (arr_new[i] == NULL)
			break ;
		free(arr[i++]);
	}
	free(arr);
	arr_new[i] = NULL;
	return (arr_new);
}
