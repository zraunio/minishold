/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_into_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:58:21 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/22 09:38:53 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

static char	*replace_dot_dot(char *new_dir, int i)
{
	char	*tmp;
	int		last_slash_index;
	char	*tmp2;

	tmp = ft_strndup(new_dir, i);
	last_slash_index = ft_return_char_index(tmp, '/', 'e');
	if (last_slash_index == 0)
	{
		free_two((void *)tmp, (void *)new_dir);
		return (ft_strdup("/"));
	}
	tmp2 = ft_strndup(tmp, last_slash_index);
	free(tmp);
	tmp = ft_strjoin(tmp2, new_dir + i + 3);
	free_two((void *)tmp2, (void *)new_dir);
	new_dir = ft_strdup(tmp);
	free(tmp);
	return (new_dir);
}

static char	*find_dot_dot(char *new_dir)
{
	long long	i;

	i = 0;
	while (new_dir[i] != '\0')
	{
		if (new_dir[i] == '/' && new_dir[i + 1] == '.' && new_dir[i + 2] == '.')
		{
			new_dir = replace_dot_dot(new_dir, i);
			if (ft_strequ(new_dir, "/"))
				return (new_dir);
			i = -1;
		}
		i++;
	}
	return (new_dir);
}

static char	*check_new_dir_slash(char *curr_dir, char *new_dir, t_shell *data)
{
	long long	i;
	char		*tmp;

	i = 0;
	tmp = NULL;
	if (new_dir[0] != '/')
	{
		i = check_if_array("CDPATH", data->environ);
		if (i == -1)
		{
			if (curr_dir[((int)ft_strlen(curr_dir) - 1)] != '/')
			{
				tmp = ft_strjoin(curr_dir, "/");
				tmp = ft_strjoin_free(tmp, new_dir, 1);
			}
			else
				tmp = ft_strjoin(curr_dir, new_dir);
			free(new_dir);
			return (tmp);
		}
		else
			ft_printf("try cdpath variable\n");
	}
	tmp = ft_strdup(new_dir);
	free(new_dir);
	return (tmp);
}

static char	*strtrim_duplicates(char *str, char c)
{
	int		i;
	size_t	x;
	char	*begin;
	char	*end;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c && str[i + 1] == c)
		{
			x = 0;
			begin = ft_strndup(str, i + 1);
			while (str[i + 1 + x] == c && str[i + 1 + x] != '\0')
				x++;
			end = ft_strdup(str + i + 1 + x);
			free(str);
			str = ft_strjoin(begin, end);
			free_two((void *)begin, (void *)end);
			i = -1;
		}
		i++;
	}
	return (str);
}

void	cd_into_dir(char *curr_dir, char *new_dir, t_shell *data, char *orig)
{
	char	*tmp;

	new_dir = strtrim_duplicates(new_dir, '/');
	new_dir = check_new_dir_slash(curr_dir, new_dir, data);
	new_dir = find_dot_dot(new_dir);
	tmp = NULL;
	if (data->p_flag)
		tmp = check_symlink_name(new_dir, curr_dir);
	if (tmp != NULL)
	{
		new_dir = ft_strdup(tmp);
		free(tmp);
	}
	if (data->prev_dir != NULL)
		free(data->prev_dir);
	data->prev_dir = ft_strdup(new_dir);
	if (check_dir_rights(new_dir, curr_dir, data, orig) == 1)
		change_directories(data, new_dir, curr_dir, orig);
}
