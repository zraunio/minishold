/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:14:39 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/11 15:06:35 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	change_pwd(t_shell *data, char *new_dir)
{
	char	*var;
	int		i;

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
		char *org_input)
{
	int		i;
	char	*var;
	int		ret;

	if (new_dir != NULL)
	{
		ret = chdir(new_dir);
		if (ret == -1)
		{
			free_two((void *)new_dir, (void *)current_dir);
			ft_printf("cd: no such file or directory: %s\n", org_input);
			return ;
		}
	}
	var = ft_strdup("OLDPWD");
	i = check_if_var_is_in_array(var, data->environ);
	if (i == -1)
		add_new_var_to_environ(data, var, current_dir);
	else
		change_old_var_value(data, var, current_dir, i);
	if (new_dir == NULL)
		return ;
	change_pwd(data, new_dir);
}

/*
** Returns the dir where we want to enter depending on what was given as input.
**
*/

static char	*cd_get_next_dir_2(t_shell *data, char *dir_name)
{
	char	*new_dir;
	int		i;

	if (ft_strequ(dir_name, "-"))
	{
		i = check_if_var_is_in_array("OLDPWD", data->environ);
		if (i == -1)
			return (NULL);
		new_dir = ft_strstr_after(data->environ[i], "OLDPWD=");
		data->previous_dir_in_cd = 1;
		return (ft_strdup(new_dir));
	}
	else
		return (ft_strdup(dir_name));
}

char	*cd_get_next_dir(t_shell *data, char *dir_name, char *current_dir)
{
	char	*new_dir;
	int		i;

	if (dir_name == NULL)
	{
		i = check_if_var_is_in_array("HOME", data->environ);
		if (i == -1)
			return (NULL);
		new_dir = ft_strstr_after(data->environ[i], "HOME=");
		return (ft_strdup(new_dir));
	}
	else if (ft_strequ(dir_name, "~") || dir_name[0] == '~')
		return (tilde_dir_name(dir_name, data));
	else if (ft_strequ(dir_name, ".") || ft_strequ(dir_name, ""))
		return (ft_strdup(current_dir));
	else if (ft_strequ(dir_name, ".."))
	{
		i = ft_return_char_index(current_dir, '/', 'e');
		if (i == 0)
			return (ft_strdup("/"));
		new_dir = ft_strndup(current_dir, i);
		return (new_dir);
	}
	return (cd_get_next_dir_2(data, dir_name));
}

/*
** First we args++ 2 to skip 'cd' word. Then we go to check_cd_arguments
** function, that checks how the input arguments for cd look like. If it
** returns -1, it means there's something wrong with the arguments. That
** function outputs error message, so here we only want to go back.
** If check_cd_arguments returns something else, we want to continue.
** Now we call ft_strsplit to get all args in array.
** We work with arr[0] (thats why i = 0). If either of the flags are 1,
** we define i = 1 so we work with different row.
*/

void	cd_function_start(char *args, t_shell *data, int i)
{
	char	**cd_args_arr;
	char	*current_dir;
	char	*new_dir;

	if (check_cd_arguments(args, data) == -1)
		return ;
	cd_args_arr = ft_strsplit(args, ' ');
	if (cd_args_arr == NULL)
		exit (1);
	while (cd_args_arr[i] != NULL)
	{
		if (cd_args_arr[i][0] != '-')
			break ;
		i++;
	}
	current_dir = get_current_dir();
	if (current_dir == NULL)
		return (free_arr((void **)cd_args_arr));
	clean_quotes_from_dir_name(cd_args_arr[i]);
	new_dir = cd_get_next_dir(data, cd_args_arr[i], current_dir);
	if (new_dir != NULL)
		cd_function_finish(current_dir, new_dir, data, cd_args_arr[i]);
	else
		free(current_dir);
	free_arr((void **)cd_args_arr);
}
