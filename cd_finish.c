/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 11:47:02 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/22 15:39:42 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*replace_dot_dot(char *new_dir, int i)
{
	char	*tmp_new;
	int		last_slash_index;
	char	*tmp_new2;

	tmp_new = ft_strndup(new_dir, i);
	last_slash_index = ft_return_char_index(tmp_new, '/', 'e');
	if (last_slash_index == 0)
	{
		free_two((void *)tmp_new, (void *)new_dir);
		return (ft_strdup("/"));
	}
	tmp_new2 = ft_strndup(tmp_new, last_slash_index);
	free(tmp_new);
	tmp_new = ft_strjoin(tmp_new2, new_dir + i + 3);
	free_two((void *)tmp_new2, (void *)new_dir);
	new_dir = ft_strdup(tmp_new);
	free(tmp_new);
	return (new_dir);
}

static char	*find_dot_dot(char *new_dir)
{
	int		i;

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

static char	*check_new_dir_slash(char *current_dir, char *new_dir,
	t_shell *data)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (new_dir[0] != '/')
	{
		i = check_if_var_is_in_array("CDPATH", data->environ);
		if (i == -1)
		{
			if (current_dir[((int)ft_strlen(current_dir) - 1)] != '/')
				tmp = ft_strjoin_three(current_dir, "/", new_dir);
			else
				tmp = ft_strjoin(current_dir, new_dir);
			free(new_dir);
			return (tmp);
		}
		else
			ft_printf("we should try cdpath variable\n");
	}
	tmp = ft_strdup(new_dir);
	free(new_dir);
	return (tmp);
}

static char	*remove_dup_characters_from_str(char *str, char c)
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

void	cd_function_finish(char *current_dir, char *new_dir, t_shell *data,
	char *orig_input)
{
	char	*tmp;

	new_dir = remove_dup_characters_from_str(new_dir, '/');
	new_dir = check_new_dir_slash(current_dir, new_dir, data);
	new_dir = find_dot_dot(new_dir);
	tmp = NULL;
	if (data->p_flag)
		tmp = check_symlink_name(new_dir, current_dir);
	if (tmp != NULL)
	{
		new_dir = ft_strdup(tmp);
		free(tmp);
	}
	if (data->prev_dir != NULL)
		free(data->prev_dir);
	data->prev_dir = ft_strdup(new_dir);
	if (check_dir_rights(new_dir, current_dir, data, orig_input) == 1)
		change_directories(data, new_dir, current_dir, orig_input);
}
