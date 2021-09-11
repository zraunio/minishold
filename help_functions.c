/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 17:45:51 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/11 17:58:51 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**add_exec_to_arr(char **arr, char *executable)
{
	int		arr_len;
	char	**new_arr;
	int		i;

	arr_len = 0;
	while (arr[arr_len] != NULL)
		arr_len++;
	new_arr = (char **)malloc(sizeof(char *) * (arr_len + 1 + 1));
	i = 0;
	new_arr[0] = ft_strdup(executable);
	while (arr[i] != NULL)
	{
		new_arr[i + 1] = ft_strdup(arr[i]);
		free(arr[i++]);
	}
	free(arr);
	new_arr[i + 1] = NULL;
	return (new_arr);
}

void	update_path_array(t_shell *data)
{
	int	i;
	int	len;

	i = 0;
	if (data->path_array != NULL)
	{
		while (data->path_array[i] != NULL)
		{
			len = ft_strlen(data->path_array[i]);
			free(data->path_array[i]);
			ft_memset((void *)data->path_array[i++], 0, len);
		}
		free(data->path_array);
		data->path_array = NULL;
	}
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
