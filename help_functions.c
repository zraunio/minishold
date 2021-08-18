/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 17:45:51 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/18 13:46:34 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
**
*/

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