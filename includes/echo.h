/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 16:09:22 by zraunio           #+#    #+#             */
/*   Updated: 2021/09/02 16:28:19 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECHO_H
#define ECHO_H

#include "../libft/incl/libft.h"

/*
** helper functions for different functionalities
*/
char	*dollar_write(char *out, char **env);
char	*quote_write(char *out, char **env, size_t n, char q);
char	*echo_write(char *out, size_t len, size_t in_or_out, size_t n);
/*
** rewrite of the echo command:
** handles Dollar $, quotes, and ~
*/
void	ft_echo(char *str, char **env);
#endif
