/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_or_null.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:27:23 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/30 14:16:41 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	check_if_null_arr(void **arr)
{
	if (arr == NULL)
		exit (1);
}

void	check_if_null_ptr(void *ptr)
{
	if (ptr == NULL)
		exit (1);
}

void	free_fork_and_child(t_shell *data, char *executable, char *args)
{
	ft_memdel((void *)&data->original_exec);
	free_two((void *)&args, (void *)&executable);
}
