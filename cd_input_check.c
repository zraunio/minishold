/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_input_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:59:34 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/15 12:58:59 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
** We loop through all dashes if there's a lot. Then we check if the next
** characters after dashes are either L or P. If we don't get either or space,
** we output error message and return -1. Otherwise we go on until next space
** and return 1.
*/

static int	check_cd_flag_end_of_input(char *args, t_shell *data)
{
	int	i;

	i = 0;
	data->i++;
	while (args[data->i] != '\0' && ft_isspace(args[data->i]))
		data->i++;
	if (args[data->i] != '\0')
		return (cd_flags_error(args, data));
	return (1);
}

static int	check_cd_flags_loop(char *args, t_shell *data)
{
	while (args[data->i] != '\0')
	{
		if (args[data->i] == 'P')
			data->p_flag = 1;
		else if (args[data->i] == 'L')
			data->l_flag = 1;
		else if (args[data->i] == ' ' && (args[data->i - 1] == 'P'
				|| args[data->i - 1] == 'L'))
			break ;
		else
			return (cd_flags_error(args, data));
		data->i++;
	}
	return (1);
}

static int	check_cd_flags(char *args, t_shell *data)
{
	int	len;

	len = 0;
	while (args[data->i] != '\0')
	{
		while (ft_isspace(args[data->i]) && args[data->i] != '\0')
			data->i++;
		if (args[data->i] == '-')
		{
			data->i++;
			if (args[data->i] == ' ' || args[data->i] == '-')
				return (check_cd_flag_end_of_input(args, data));
			if (check_cd_flags_loop(args, data) == -1)
				return (-1);
		}
		else if (!ft_isspace(args[data->i]))
			return (1);
	}
	return (1);
}

/*
** Initialize some values to zero.
*/

void	set_cd_values_to_zero(t_shell *data)
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
