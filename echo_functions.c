/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 17:46:40 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/02 17:13:04 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	write_echo_output(char *echo_arg, int output_len, int in_or_out,
	int quote)
{
	int i;

	i = 0;
	while (echo_arg[i] != '\0' && i < output_len)
	{
		while (echo_arg[i] == '\\')
		{
			if (in_or_out == 2 && (echo_arg[i + 1]
				== 'n' || (echo_arg[i + 1] == '\\' && echo_arg[i + 2] == 'n')
				|| echo_arg[i + 1] == 't' || (echo_arg[i + 1] == '\\' 
					&& echo_arg[i + 2] == 't')))
			{
				if (echo_arg[i + 1] == 'n' || echo_arg[i + 2] == 'n')
					write(1, "\n", 1);
				else if (echo_arg[i + 1] == 't' || echo_arg[i + 2] == 't')
					write(1, "\t", 1);
				if (echo_arg[i + 1] == '\\' && (echo_arg[i + 2] == 'n'
					|| echo_arg[i + 2] == 't'))
					i++;
				i += 2;
			}
			else if (in_or_out == 0)
			{
				if (echo_arg[i + 1] == '\\' && (echo_arg[i + 2] == 'n'
					|| echo_arg[i + 2] == 't'))
				{
					if (echo_arg[i + 2] == 'n')
						write(1, "\n", 1);
					else if (echo_arg[i + 2] == 't')
						write(1, "\t", 1);
					i += 3;
				}
				i++;
			}
			else if (in_or_out == 2)
			{
				i++;
				if (echo_arg[i + 1] == ' ')
					write(1, &echo_arg[i++], 1);
			}
		}
		if ((echo_arg[i] == '"' && (quote == 2 || quote == 0)) || (echo_arg[i] == '\''
			&& (quote == 1 || quote == 0)) || echo_arg[i] == '\0')
			break ;
		write(1, &echo_arg[i++], 1);
	}
}


static void	path_write(char *tmp, char *env)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(tmp);
	i = 0;
	ft_memdel((void *)&tmp);
	tmp = ft_strdup(&env[len + 1]);
	while (tmp[i] != '\0')
	{
		if (tmp[i] == ':')
			tmp[i] = ' ';
		i++;
	}
	ft_putstr(tmp);
}

static char *find_start(char *out)
{
	size_t	i;
	char *tmp;

	i = 0;
	if (ft_isspace(out[i]) == 1)
		return (out);
	while (ft_isspace(out[i]) == 0 && out[i] != '"' && out[i] != '\0')
		i++;
	tmp = ft_strsub(out, 0, i);
	if (!tmp)
	{
		write (1, "find_start", 11);
		exit (1);
	}
	i = 0;
	while (tmp[i++])
		if (tmp[i] >= 97 || tmp[i] <= 122)
			tmp[i] = ft_toupper(tmp[i]);
	return (tmp);
}

char	*print_dollar(char **env, char *out)
{
	size_t	i;
	size_t	j;
	char	*tmp;
	char	*cmp;

	i = 0;
	tmp = find_start(out);
	j = ft_strlen(tmp);
	while (env[i] != NULL)
	{
		cmp = ft_strstr(env[i], tmp);
		if (cmp != NULL)
		{
			if (ft_strcmp(tmp, "PATH") == 0)
				path_write(tmp, env[i]);
			else
				ft_putstr(&env[i][j + 1]);
			break ;
		}
		else
			i++;
	}
	ft_memdel((void *)&tmp);
	if (out[j] == '"')
		j++;
	if (env[i] == NULL && out[j - 1] == '"')
		write(1, " ", 1);
	return (out + j);
}

char	*print_quotes(char *out, char **env, int n, char q)
{
		size_t	i;

	i = 0;
	if (out[1] == '\0')
	{
		if ((q == '"' && out[i] == '"' && n != 1) || (q == '\''
		&& out[i] == '\'' && n != 2))
			write(1, "\n", 1);
		return (out + 1);
	}
	while (out[i] != '\0')
	{
		if (out[i] == '$')
		{
			if (i > 1)
				write_echo_output(out, i, 2, n);
			out = print_dollar(env, &out[i + 1]);
			if (out[0] == '\0')
				return (out);
			i--;
		}
		else if ((q == '"' && out[i] == '"' && n == 2 && out[i - 1] != '\\')
		|| (q == '\'' && out[i] == '\'' && n == 1))
			break ;
		i++;
	}
	if (i == 0)
		return (out);
	write_echo_output(out, i, 2, n);
	return (&out[i + 1]);
}

char	*print_text_after_pipe_or_semicolon(char *echo_arg, int quote)
{
	int i;

	i = 0;
	while (echo_arg[i] != '\0')
	{
		if (echo_arg[i] == '"' || echo_arg[i] == '\'' || echo_arg[i] == '$')
			break ;
		i++;
	}
	write_echo_output(echo_arg, i, 0, quote);
	return (echo_arg + i);
}
