/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 19:02:36 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/26 12:10:19 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	**ft_arrdup(char **arr)
{
	int		rows;
	int		i;
	char	**copy_of_arr;

	rows = 0;
	while (arr[rows] != NULL)
		rows++;
	copy_of_arr = (char **)malloc(sizeof(char *) * (rows + 1));
	if (copy_of_arr == NULL)
		exit (1);
	i = 0;
	while (arr[i] != NULL)
	{
		copy_of_arr[i] = ft_strdup(arr[i]);
		if (copy_of_arr[i] == NULL)
			exit (1);
		free(arr[i++]);
	}
	free(arr);
	copy_of_arr[i] = NULL;
	return (copy_of_arr);
}
