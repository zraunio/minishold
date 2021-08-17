/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:57:03 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/17 17:41:41 by ehelmine         ###   ########.fr       */
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
	if (echo_arg[i] == ' ')
		return (echo_arg);
	while (echo_arg[i] != ' ' && echo_arg[i] != '"' && echo_arg[i] != '\n'
		&& echo_arg[i] != '\0')
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
			break ;
		}
		else
			i++;
	}
	free(temp);
	temp = NULL;
	if (echo_arg[len] == '"')
		len++;
	if (environ[i] == NULL && echo_arg[len - 1] == '"')
		write(1, " ", 1);	
	return (echo_arg + len);	
}

char	*print_double_quotes(char *echo_arg, char **copy_of_environ)
{
	int i;

	i = 0;
	if (echo_arg[i] == '"' && echo_arg[i + 1] == '\0')
	{
		write(1, "\n", 1);
		return (echo_arg + 1);
	}
	while (echo_arg[i] != '\0')
	{
		if (echo_arg[i] == '$')
		{
			if (i > 1)
				write(1, echo_arg, i);
			echo_arg = print_dollar(copy_of_environ, echo_arg + i + 1);
			if (echo_arg[0] == '\0')
				return (echo_arg);
			i = -1;
		}
		else if (echo_arg[i] == '"')
			break ;
		i++;
	}
	if (i == 0)
		return (echo_arg);
	write(1, echo_arg, i);
	return (echo_arg + i + 1);
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
				echo_arg = print_dollar(copy_of_environ, echo_arg + i + 1);
				i = 0;
			}
			else if (echo_arg[i] == '"')
			{
				echo_arg = print_double_quotes(echo_arg + i + 1, copy_of_environ);
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

int	check_amount_of_quotes(char *args)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (args[i] != '\0')
	{
		if (args[i] == '"')
			x++;
		i++;
	}
	return (x);
}

void	loop_double_quotes(char *args, int am_of_quotes)
{
	char *buf;
	char **buf_arr;

	buf = (char *)malloc(sizeof(char) * 500);
	if (buf == NULL)
		exit (1);
	while (am_of_quotes % 2 != 0)
	{
		write(1, "dquote> ", 8);
		ft_memset((void *)buf, 0, 500);
		buf[0] = '\n';
		loop_input_to_string(buf + 1);
		buf_arr = split_input_to_array(buf);
		ft_strcat(args, buf_arr[0]);
		am_of_quotes = check_amount_of_quotes(args);
	}
	free(buf);
}

void	execute_built_in(char *built_in, char **copy_of_environ, char **args)
{
	int i;
	int am_of_quotes;

	i = 0;
	if (built_in[0] == 'e' && built_in[1] == 'x')
		exit (0);
	else if (built_in[0] == 'c')
		ft_printf("--im cd |%s|\n", built_in);
	else if (built_in[0] == 'e' && built_in[1] == 'c')
	{
		am_of_quotes = check_amount_of_quotes(args[0]);
		if (am_of_quotes % 2 != 0)
			loop_double_quotes(args[0], am_of_quotes);
		my_echo(args[0], copy_of_environ);
	}
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