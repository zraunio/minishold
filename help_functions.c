/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 17:45:51 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/02 16:57:49 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
** MAX_LEN of dir is 4096. Allocate memory, get current directory & return it.
*/

char	*get_current_dir(void)
{
	char	*current_dir;

	current_dir = (char *)malloc(sizeof(char) * 4096);
	if (current_dir == NULL)
		exit (1);
	getcwd(current_dir, 4096);
	return (current_dir);
}

/*
**
*/

void	remove_one_string_in_array(char **array, int row)
{
	while (array[row + 1] != NULL)
	{
		free(array[row]);
		array[row] = ft_strnew((int)ft_strlen(array[row + 1]));
		ft_strcpy(array[row], array[row + 1]);
		row++;
	}
	free(array[row]);
	array[row] = NULL;
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
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 65 && str[i] <= 90)
			str[i] -= 32;
		i++;
	}
}
