/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:14:39 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/26 17:25:43 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
**	the path name of the working directory. Buffer must be big enough to hold the
**	working directory name, plus a terminating NULL to mark the end of the name.
**	Returned value
**	If successful, getcwd() returns a pointer to the buffer.
**	
**	If unsuccessful, getcwd() returns a NULL pointer and sets errno (dif values).
*/

void	change_directory(t_shell *data, char *new_pwd)
{
	char	*buf;
	int		i;
	char	*new_dir;
	char	*tmp;
	char	*tmp2;

	buf = (char *)malloc(sizeof(char) * 256);
	if (buf == NULL)
		exit (1);
	getcwd(buf, 256);
	tmp = ft_strdup("OLDPWD");
	if (ft_strequ("HOME", new_pwd))
	{
		i = check_if_var_is_in_array("OLDPWD", data->copy_of_environ);
		if (i == -1)
			add_new_var_to_environ(data, tmp, buf);
		else
			change_old_var_value(data, tmp, buf, i);
		i = check_if_var_is_in_array("HOME", data->copy_of_environ);
		new_dir = ft_strstr_after(data->copy_of_environ[i], "HOME=");
		tmp2 = ft_strdup(new_dir);
		if (tmp2 != NULL)
		{
			chdir(tmp2);
			tmp = ft_strdup("PWD");
			i = check_if_var_is_in_array("PWD", data->copy_of_environ);
			change_old_var_value(data, tmp, tmp2, i);
		}
	}
}

/**
**
**
*/

void	check_given_directory(char *args, t_shell *data)
{
	args += 3;
	if (args[0] == '\0')
	{
		ft_printf("no arguments for cd so if we are not home, we have to go\n");
		change_directory(data, "HOME");
	}
	else if ((args[0] == '.' && args[1] != '.') || (args[0] == '.' &&
			args[1] == '.' && args[2] != '.'))
		ft_printf("its either a . or .. beginning dir\n");
	else if (args[0] == '/')
		ft_printf("set curpath to the operand\n");
	else
		ft_printf("we check cdpath %s\n", data->copy_of_environ[0]);
}