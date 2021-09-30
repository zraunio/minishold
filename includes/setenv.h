/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:27:25 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/30 11:58:26 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETENV_H
#define SETENV_H

# include "minishell.h"

void	env_new_var(t_shell *data, char *var, char *value);
char	*env_check_int(char *args, char *var, char *value);
void	env_var_change(t_shell *data, char *var, char *val, int i);
/*
** Library setenv function:
**    int setenv(const char *name, const char *value, int overwrite);
*/
void	ft_setenv(t_shell *data, char *args);

#endif
