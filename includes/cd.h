/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:41:42 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/30 11:17:13 by zraunio          ###   ########.fr       */
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
int		check_dir_rights(char *new_dir, char *curr_dir, t_shell *data, char *orig);
char	*tilde_dir(char *dir_name, t_shell *data);
/*
** rewrite of the cd command
*/
void	ft_cd(char *args, t_shell *data, size_t i);

#endif
