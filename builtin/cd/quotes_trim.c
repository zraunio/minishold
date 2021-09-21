/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:46:04 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/21 10:47:47 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

void	quotes_trim(char *dir)
{
	size_t	i;
	size_t	len;
	char	*tmp;

	tmp = NULL;
	if (dir == NULL)
		return ;
	i = 0;
	len = ft_strlen(dir);
	if ((dir[0] == '"' && dir[len - 1] == '"') || (dir[0] == '\'' && dir[len - 1]
			== '\''))
	{
		tmp = ft_strndup(dir + 1, len - 2);
		ft_memset((void *)dir, 0, len);
		ft_strcpy(dir, tmp);
		free(tmp);
	}
}
