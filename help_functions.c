/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 17:45:51 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/20 15:49:37 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
**
*/

void	ft_putarr(char **arr)
{
	int i;
	int x;

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

char	*return_string_before_given_character(char *str, char c)
{
	int		i;
	char	*new_str;

	i = 0;
	if (c == '\0')
	{
		new_str = ft_strdup(str);
		return (new_str);
	}
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			new_str = ft_strndup(str, i);
			return (new_str);
		}
		i++;
	}
	return (NULL);
}

void	change_to_uppercase(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_islower(str[i]))
			str[i] -= 32;
		i++;
	}
}