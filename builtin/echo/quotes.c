/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 15:58:28 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/02 16:47:55 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*quote_write(char *out, char **env, size_t n, char q)
{
	size_t	i;

	i = 0;
	if (out[1] == '\0')
	{
		if ((q == '"' && out[i] == '"' && n != 1) || (q == '\''
		&& out[i] == '\'' && n != 2))
			write(1, "\n", 1);
		return (out + 1);
	}
	while (out[i] != '\0')
	{
		if (out[i] == '$')
		{
			if (i > 1)
				echo_write(out, i, 2, n);
			out = dollar_write(env, &out[i + 1]);
			if (out[0] == '\0')
				return (out);
			i--;
		}
		else if ((q == '"' && out[i] == '"' && n == 2 && out[i - 1] != '\\')
		|| (q == '\'' && out[i] == '\'' && n == 1))
			break ;
		i++;
	}
	if (i == 0)
		return (out);
	echo_write(out, i, 2, n);
	return (&out[i + 1]);
}
