/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 16:16:54 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/09 10:42:53 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*echo_write(char *out, size_t len, size_t in_or_out, size_t n)
{
	size_t i;

	i = 0;
	while (out[i] && i < len)
	{
		while (out[i] == '\\')
		{
			if (in_or_out == 2 && (out[i + 1] == 'n'
			|| (out[i + 1] == '\\' && out[i + 2] == 'n') || out[i + 1] == 't' 
			|| (out[i + 1] == '\\' && out[i + 2] == 't')))
			{
				if (out[i + 1] == 'n' || out[i + 2] == 'n')
					write(1, "\n", 1);
				else if (out[i + 1] == 't' || out[i + 2] == 't')
					write(1, "\t", 1);
				if (out[i + 1] == '\\' && (out[i + 2] == 'n'
					|| out[i + 2] == 't'))
					i++;
				i += 2;
			}
		}
	}
}
