/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_or_null.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:27:23 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/08 16:46:42 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	check_if_null(void *ptr)
{
	if (ptr == NULL)
		exit (1);
}

void	free_fork_and_child(t_shell *data, char *executable, char *args)
{
	if (data->original_exec != NULL)
	{
		free(data->original_exec);
		data->original_exec = NULL;
	}
	if (args != NULL)
		free(args);
	free(executable);
}
