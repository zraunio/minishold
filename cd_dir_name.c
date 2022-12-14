/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_dir_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:40:11 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/24 22:37:36 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	clean_quotes_from_dir_name(char *d)
{
	int		i;
	size_t	len;
	char	*tmp;

	tmp = NULL;
	if (d == NULL)
		return ;
	i = 0;
	len = ft_strlen(d);
	if ((d[0] == '"' && d[len - 1] == '"') || (d[0] == '\'' && d[len - 1]
			== '\''))
	{
		tmp = ft_strndup(d + 1, len - 2);
		ft_memset((void *)d, 0, len);
		ft_strcpy(d, tmp);
		ft_memdel((void *)&tmp);
	}
}

char	*tilde_dir_name(char *dir_name, t_shell *data)
{
	int		i;
	char	*new_dir;
	char	*home;
	char	*end;

	i = check_if_var_is_in_array("HOME", data->environ);
	if (i == -1)
		return (NULL);
	home = ft_strstr_after(data->environ[i], "HOME=");
	if (ft_strequ(dir_name, "~"))
		return (ft_strdup(home));
	else
	{
		end = ft_strdup(dir_name + 1);
		new_dir = ft_strjoin(home, end);
		ft_memdel((void *)&end);
		return (new_dir);
	}
	return (NULL);
}
