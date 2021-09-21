/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:41:42 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/21 11:13:21 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
#define CD_H

# include "../libft/incl/libft.h"
# include "minishell.h"

int		cd_args_check(char *args, t_shell *data);
void	dir_compare(char *curr_dir, t_shell *data);
void	cd_into_dir(char *curr_dir, char *new_dir, t_shell *data, char *orig);
char	*get_current_dir(void);
void	quotes_trim(char *dir);
/*
** rewrite of the cd command
*/
void	ft_cd(char *args, t_shell *data, size_t i);

#endif
