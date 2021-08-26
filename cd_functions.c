/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:14:39 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/26 15:22:33 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	check_given_directory(char *args, t_shell *data)
{
	args += 3;
	if (args[0] == '\0')
		ft_printf("no arguments for cd\n");
	else if ((args[0] == '.' && args[1] != '.') || (args[0] == '.' &&
			args[1] == '.' && args[2] != '.'))
		ft_printf("its either a . or .. beginning dir\n");
	else if (args[0] == '/')
		ft_printf("set curpath to the operand\n");
	else
		ft_printf("we check cdpath %s\n", data->copy_of_environ[0]);
}