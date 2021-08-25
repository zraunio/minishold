/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 19:03:09 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/25 19:03:34 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putarr(char **arr)
{
	int	x;
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		x = 0;
		while (arr[i][x] != '\0')
			x++;
		write(1, arr[i++], x);
		write(1, "\n", 1);
	}
}
