/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 18:08:25 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/22 15:39:56 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	change_pwd(t_shell *data, char *new_dir)
{
	char	*var;
	int		i;

	if (new_dir == NULL)
		return ;
	var = ft_strdup("PWD");
	i = check_if_var_is_in_array(var, data->environ);
	if (i == -1)
		add_new_var_to_environ(data, var, new_dir);
	else
		change_old_var_value(data, var, new_dir, i);
	if (data->previous_dir_in_cd)
	{
		var = ft_strdup("PWD");
		i = check_if_var_is_in_array(var, data->environ);
		ft_printf("%s\n", data->environ[i] + 4);
		data->previous_dir_in_cd = 0;
		free(var);
	}
}

/*
**	int chdir(const char *pathname);
**	Makes pathname your new working directory.
**
**	Returned value
**	If successful, chdir() changes the working directory and returns 0.
**	If unsuccessful, chdir() does not change the working directory, returns -1,
**	and sets errno to one of the following values:
**
**
**	char *getcwd(char *buffer, size_t size);
**	Determines the path name of the working directory and stores it in buffer.
**	size = The number of characters in the buffer area.
**	buffer = The name of the buffer that will be used to hold
**	the path name of the working directory. Buffer must be big enough to hold
** the working directory name, plus a terminating NULL to mark the end of the
** name.
**	Returned value
**	If successful, getcwd() returns a pointer to the buffer.
**	
**	If unsuccessful, getcwd() returns a NULL pointer and sets errno (different
** values).
*/

void	change_directories(t_shell *data, char *new_dir, char *current_dir,
		char *orig_input)
{
	int		i;
	char	*var;

	if (new_dir != NULL)
	{
		if (chdir(new_dir) == -1)
		{
			free_two((void *)new_dir, (void *)current_dir);
			ft_printf("cd: no such file or directory: %s\n", orig_input);
			if (data->prev_dir != NULL)
			{
				free(data->prev_dir);
				data->prev_dir = NULL;
			}
			return ;
		}
	}
	var = ft_strdup("OLDPWD");
	i = check_if_var_is_in_array(var, data->environ);
	if (i == -1)
		add_new_var_to_environ(data, var, current_dir);
	else
		change_old_var_value(data, var, current_dir, i);
	change_pwd(data, new_dir);
}

static char	*get_new_symlink_dir(char *new_dir, char *current_dir)
{
	char	*tmp_current;

	tmp_current = NULL;
	tmp_current = get_current_dir();
	chdir(current_dir);
	if (ft_strequ(tmp_current, new_dir))
	{
		free(tmp_current);
		return (NULL);
	}
	else
	{
		free(new_dir);
		new_dir = ft_strdup(tmp_current);
		free(tmp_current);
		return (new_dir);
	}	
}

char	*check_symlink_name(char *new_dir, char *current_dir)
{
	struct stat	b;
	int			i;

	i = lstat(new_dir, &b);
	if (i == 0 && b.st_mode & S_ISLNK(b.st_mode))
	{
		i = chdir(new_dir);
		if (i != -1)
			return (get_new_symlink_dir(new_dir, current_dir));
	}
	return (NULL);
}

void	compare_current_dir_to_prev(char *current_dir, t_shell *data)
{
	if (data->prev_dir == NULL)
		return ;
	if (ft_strequ(current_dir, data->prev_dir))
		return ;
	ft_memset((void *)current_dir, 0, 4096);
	ft_strcpy(current_dir, data->prev_dir);
}
