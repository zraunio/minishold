/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_input_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:59:34 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/30 21:57:56 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
** i marks the place we were after while loop. X is in the beginning zero.
** If args points to space, we loop through spaces (because it is fine to have
** multiple spaces in the end of cd argument). If after spaces we are at '\0',
** everything's fine and we return 1. Otherwise our argument is kind of ruined,
** and we are gonna output error message and return -1.
*/

static int	check_cd_last_space(char *args, t_shell *data)
{
	while (args[data->i + data->x] == ' ' && args[data->i + data->x] != '\0')
		data->x++;
	if (args[data->i + data->x] == '\0')
		return (1);
	else
	{
		ft_printf("cd: string not in pwd: ");
		write(1, args + (data->i - data->len_of_dir), data->len_of_dir);
		write(1, "\n", 1);
		return (-1);
	}	
}

/*
** We loop through all dashes if there's a lot. Then we check if the next
** characters after dashes are either L or P. If we don't get either or space,
** we output error message and return -1. Otherwise we go on until next space
** and return 1.
*/

static int	check_cd_flags(char *args, t_shell *data)
{
	while (args[data->i] == '-')
		data->i++;
	while (args[data->i] != ' ' && args[data->i] != '\0')
	{
		if (args[data->i] == 'L')
			data->l_flag = 1;
		else if (args[data->i] == 'P')
			data->p_flag = 1;
		else
		{
			ft_printf("cd: string not in pwd: ");
			write(1, args, data->i + 1);
			write(1, "\n", 1);
			return (-1);
		}
		data->i++;
	}
	if (data->l_flag == 0 && data->p_flag == 0)
		return (-1);
	return (1);
}

/*
** Initialize some values to zero.
*/

static void	set_cd_values_to_zero(t_shell *data)
{
	data->l_flag = 0;
	data->p_flag = 0;
	data->i = 0;
	data->x = 0;
	data->len_of_dir = 0;
}

/*
** We have string *args, that has all the arguments for cd.
** We can't trim all whitespaces from beginning and the end, 'cause
** for example newlines are considered as input. So when we go and loop
** through it, we check these things:
** 1. check given flags (possible ones: P and L) and if error, we return -1
** 2. we loop through possible spaces
** 3. then we loop through the given directory name and get the len for that
** 4. if we get into a space after dir name, we break from while loops
** 5. then we check out of loops if our *args points to space:
** we do that check in check_cd_last_space.
*/

int	check_cd_arguments(char *args, t_shell *data)
{
	set_cd_values_to_zero(data);
	while (args[data->i] != '\0')
	{
		while (args[data->i] == ' ' && args[data->i] != '\0')
			data->i++;
		if (args[data->i] == '-')
		{
			if (check_cd_flags(args, data) == -1)
				return (-1);
		}
		while (args[data->i] == ' ' && args[data->i] != '\0')
			data->i++;
		while (args[data->i] != ' ' && args[data->i] != '\0')
		{
			data->i++;
			data->len_of_dir++;
			if (args[data->i] == ' ')
				break ;
		}
		if (args[data->i] == ' ')
			break ;
	}
	if (args[data->i] == ' ')
		check_cd_last_space(args, data);
	return (1);
}
