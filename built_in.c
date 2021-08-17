/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:57:03 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/17 14:48:06 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
**
*/

void	change_to_uppercase(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_islower(str[i]))
			str[i] -= 32;
		i++;
	}
}

char	*print_dollar(char **environ, char *echo_arg)
{
	int i;
	int len;
	char *temp;
	int x;
	char *check;

	i = 0;
	echo_arg++;
	if (echo_arg[i] == ' ')
		return (echo_arg);
	while (echo_arg[i] != ' ' && echo_arg[i] != '"' && echo_arg[i] != '\0')
		i++;
	temp = NULL;
	temp = ft_strndup(echo_arg, i);
	change_to_uppercase(temp);
	i = 0;
	len = ft_strlen(temp);
	while (environ[i] != NULL)
	{
		check = ft_strstr(environ[i], temp);
		if (check != NULL)
		{
			x = 0;
			if (ft_strcmp(temp, "PATH") == 0)
			{
				free(temp);
				temp = ft_strdup(environ[i] + (ft_strlen(temp) + 1));
				while (temp[x] != '\0')
				{
					if (temp[x] == ':')
						temp[x] = ' ';
					x++;
				}
				ft_putstr(temp);
			}
			else
				ft_putstr(environ[i] + ft_strlen(temp) + 1);
			if (echo_arg + len != NULL)
				write(1, " ", 1);
			free(temp);
			temp = NULL;
			return (echo_arg + len);
		}
		else
			i++;
	}
	free(temp);
	return (echo_arg + len);	
}

char	*print_double_quotes(char *echo_arg, char **copy_of_environ)
{
	int i;
	char *print_me;
	int x;
	char *tmp;

	i = 1;
	while (echo_arg[i] != '\0')
	{
		if (echo_arg[i] == '$')
		{
			if (i > 1)
				write(1, echo_arg + 1, i - 1);
			tmp = ft_strchr(echo_arg, '$');
			x = 0;
			while (tmp[x] != '\0')
			{
				if (tmp[x] == ' ')
					break ;
				x++;
			}
			print_me = ft_strndup(tmp, x);
			echo_arg = print_dollar(copy_of_environ, print_me);
			echo_arg = tmp + (ft_strlen(print_me));
			free(print_me);
			if (echo_arg[0] == '\0')
				return (echo_arg);
			i = -1;
		}
		else if (echo_arg[i] == '"')
			break ;
		i++;
	}
	if (i == 0)
		return (echo_arg + i);
	if (i == 2)
	{
		write(1, " ", 1);
		return (echo_arg + i);
	}
	print_me = ft_strndup(echo_arg + 1, i - 1);
	ft_putstr(print_me);
	free(print_me);
	if (echo_arg + i != NULL)
		write(1, "  ", 1);
	return (echo_arg + i);
}

char	*print_text(char *echo_arg)
{
	int i;

	i = 0;
	while (echo_arg[i] != '\0')
	{
		if (echo_arg[i] == '"' || echo_arg[i] == '$')
			break ;
		i++;
	}
	if (i < (int)ft_strlen(echo_arg))
		write(1, echo_arg, i);
	else
		ft_putstr(echo_arg);
	return (echo_arg + i);
}

void	my_echo(char *input, char **copy_of_environ)
{
	int i;
	char *echo_arg;
	char *tmp;
	
	i = 0;
	tmp = NULL;
	while (input[i] == ' ')
		i++;
	input += i;
	echo_arg = ft_strstr(input, " ");
	if (echo_arg != NULL)
	{
		i = 0;
		while (echo_arg[i] != '\0')
		{
			while (echo_arg[i] == ' ')
				i++;
			if (echo_arg[i] == '$')
			{
				echo_arg = print_dollar(copy_of_environ, echo_arg + i);
				i = 0;
			}
			else if (echo_arg[i] == '"')
			{
				echo_arg = print_double_quotes(echo_arg + i, copy_of_environ);
				i = 0;
			}
			else if (echo_arg[i] != '|' || echo_arg[i] != ';')
			{
				echo_arg = print_text(echo_arg + i);
				i = 0;
			}
		}
	}
	write(1, "\n", 1);
	return ;	
}

void	execute_built_in(char *built_in, char **copy_of_environ, char **args)
{
	int i;

	i = 0;
	if (built_in[0] == 'e' && built_in[1] == 'x')
		exit (0);
	else if (built_in[0] == 'c')
		ft_printf("--im cd |%s|\n", built_in);
	else if (built_in[0] == 'e' && built_in[1] == 'c')
		my_echo(args[0], copy_of_environ);
	else if (built_in[0] == 's')
		ft_printf("--im setenv |%s|\n", built_in);
	else if (built_in[0] == 'u')
		ft_printf("--im unsetenv |%s|\n", built_in);
	else
	{
		while (copy_of_environ[i] != NULL)
			ft_printf("%s\n", copy_of_environ[i++]);
	}
}