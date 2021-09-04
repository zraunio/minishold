/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 17:45:51 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/04 16:12:19 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	update_path_array(t_shell *data)
{
	free_arr((void **)data->path_array);
	get_paths_to_array(data);
}

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

char	*return_string_before_given_char(char *str, char c)
{
	int		i;

	i = 0;
	if (c == '\0')
		return (ft_strdup(str));
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (ft_strndup(str, i));
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
		if (ft_islower(str[i]))
			str[i] -= 32;
		i++;
	}
}
