/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:56:50 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/30 13:00:51 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3)
{
	char	*nwstr;
	size_t	i;
	size_t	ii;

	nwstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
			+ ft_strlen(s3) + 1));
	if (nwstr == NULL)
		exit (1);
	i = 0;
	while (s1[i] != '\0')
	{
		nwstr[i] = s1[i];
		i++;
	}
	ii = 0;
	while (s2[ii] != '\0')
		nwstr[i++] = s2[ii++];
	ii = 0;
	while (s3[ii] != '\0')
		nwstr[i++] = s3[ii++];
	nwstr[i] = '\0';
	return (nwstr);
}
