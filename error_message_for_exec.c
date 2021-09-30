/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message_for_exec.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:32:24 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/30 12:32:31 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*error_message_not_exec(char *if_exec)
{
	int	i;

	i = 0;
	while (if_exec[i] != '\0')
	{
		if (if_exec[i] == '/')
		{
			ft_printf("minishell: permission denied: %s\n", if_exec);
			break ;
		}
		i++;
	}
	if (if_exec[i] == '\0')
		ft_printf("minishell: command not found: %s\n", if_exec);
	ft_memdel((void *)&if_exec);
	return (NULL);
}
