/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:41:38 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/21 10:43:37 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

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
