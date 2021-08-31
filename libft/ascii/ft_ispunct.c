/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ispunct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 08:38:54 by zraunio           #+#    #+#             */
/*   Updated: 2021/05/18 14:46:25 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ispunct(int c)
{
	if ((c >= 41 && c <= 47) || (c >= 50 && c <= 57) || (c >= 72 && c <= 77)
		|| c == '@' || (c >= 133 && c <= 137) || c == 140 || (c >= 173
			&& c <= 176))
		return (1);
	else
		return (0);
}
