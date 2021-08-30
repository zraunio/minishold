/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:14:39 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/30 18:37:38 by ehelmine         ###   ########.fr       */
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
**	the path name of the working directory. Buffer must be big enough to hold
** the working directory name, plus a terminating NULL to mark the end of the
** name.
**	Returned value
**	If successful, getcwd() returns a pointer to the buffer.
**	
**	If unsuccessful, getcwd() returns a NULL pointer and sets errno (different
** values).
*/

void	change_directories(t_shell *data, char *new_dir, char *current_dir)
{
	int		i;
	char	*var;
	int		ret;

	ret = chdir(new_dir);
	if (ret == -1)
	{
		free_two((void *)new_dir, (void *)current_dir);
		ft_printf("cd: no such file or directory: %s\n", new_dir);
		return ;
	}
	var = ft_strdup("OLDPWD");
	i = check_if_var_is_in_array(var, data->copy_of_environ);
	if (i == -1)
		add_new_var_to_environ(data, var, current_dir);
	else
		change_old_var_value(data, var, current_dir, i);
	var = ft_strdup("PWD");
	i = check_if_var_is_in_array(var, data->copy_of_environ);
	if (i == -1)
		add_new_var_to_environ(data, var, new_dir);
	else
		change_old_var_value(data, var, new_dir, i);
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

char	*cd_get_next_dir(t_shell *data, char *dir_name, char *current_dir)
{
	char	*new_dir;
	int		i;

	if (dir_name == NULL)
	{
		i = check_if_var_is_in_array("HOME", data->copy_of_environ);
		if (i == -1)
			return (NULL);
		else
		{
			new_dir = ft_strstr_after(data->copy_of_environ[i], "HOME=");
			return (ft_strdup(new_dir));
		}
	}
	else if (ft_strequ(dir_name, "."))
		return (ft_strdup(current_dir));
	else if (ft_strequ(dir_name, ".."))
	{
		i = check_if_var_is_in_array("OLDPWD", data->copy_of_environ);
		if (i == -1)
			return (NULL);
		else
		{
			new_dir = ft_strstr_after(data->copy_of_environ[i], "PWD=");
			return (ft_strdup(new_dir));
		}
	}
	else
		return (ft_strdup(dir_name));
	return (NULL);
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

void	cd_function_start(char *args, t_shell *data)
{
	char	**cd_args_arr;
	int		check;
	int		i;
	char	*current_dir;
	char	*new_dir;

	args += 2;
	check = check_cd_arguments(args, data);
	if (check == -1)
		return ;
	cd_args_arr = ft_strsplit(args, ' ');
	if (cd_args_arr == NULL)
		exit (1);
	i = 0;
	if (data->l_flag || data->p_flag)
		i = 1;
	current_dir = get_current_dir();
	if (current_dir == NULL)
	{
		ft_printf("current directory fail\n");
		free_arr((void **)cd_args_arr);
		return ;
	}
	new_dir = cd_get_next_dir(data, cd_args_arr[i], current_dir);
	change_directories(data, new_dir, current_dir);
	free_arr((void **)cd_args_arr);
	// ADD THESE:
	// IF WE GO ../something FOR EXAMPLE, WE NEED TO ADD
	// BEFORE THAT OUR HOME PATH SO BASICALLY /USERS/EHELMINE/../SOMETHING
	// IT HAS TO USE THAT AND PUT THAT TO PWD ALSO
	// AND!!!!! INSTEAD OF DOTS, IT NEEDS TO PUT THE DIR NAME THERE. YES.
	// SO BASICALLY IF WE GO ../FT_PRINTF FROM HERE,
	// PATH WOULD BE /USERS/EHELMINE/SOMETHING IN PWD
	// SO CAN WE JUST TAKE THOSE DOTS AWAY WHEN TESTING? YES???
	// ALSO WE NEED TO CHECK IF THE WANTED DIR IS GONNA BE ACCESSIBLE
	// --->> LSTAT TO CHECK IF ITS A DIR && HAS RIGHTS TO ENTER
	// IF NOT THEN ERROR MESSAGE ABOUT 1. NOT DIR OR 2. NO RIGHTS
	// --->> LSTAT TO CHECK IF ITS A LINK OR NOT
	// IF YES, THEN WE CHECK IF -P FLAG IS THERE AND IF YES,
	// WE USE LINKNAME TO ENTER THAT
	
	/*

       The following options shall be supported by the implementation:

       -L        Handle the operand dot-dot logically; symbolic link
                 components shall not be resolved before dot-dot
                 components are processed (see steps 8.  and 9. in the
                 DESCRIPTION).

       -P        Handle the operand dot-dot physically; symbolic link
                 components shall be resolved before dot-dot components
                 are processed (see step 7. in the DESCRIPTION).

       If both -L and -P options are specified, the last of these
       options shall be used and all others ignored. If neither -L nor
       -P is specified, the operand shall be handled dot-dot logically;
       see the DESCRIPTION.

	*/
}