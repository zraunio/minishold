/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:57:03 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/16 16:45:03 by ehelmine         ###   ########.fr       */
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

	i = 0;
	echo_arg++;
	while (echo_arg[i] != ' ' && echo_arg[i] != '\0')
		i++;
	temp = ft_strndup(echo_arg, i);
	change_to_uppercase(temp);
	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strstr(environ[i], temp))
		{
			len = ft_strlen(temp);
			free(temp);
			ft_putstr(environ[i]);
			return (echo_arg + len);
		}
		else
			i++;
	}
	return (NULL);	
}

void	my_echo(char *input, char **copy_of_environ)
{
	int i;
	char *echo_arg;
	int len;
	
	i = 0;
	while (input[i] == ' ')
		i++;
	input += i;
	echo_arg = ft_strstr(input, " ");
	if (echo_arg != NULL)
	{
		echo_arg++;
		if (echo_arg[0] == '$')
			echo_arg = print_dollar(copy_of_environ, echo_arg);
		if (echo_arg[0] != '\0' && (echo_arg[0] != ';' || echo_arg[0] != '|'))
		{
			if (echo_arg[0] == '"')
				echo_arg++;
			len = ft_strlen(echo_arg);
			if (echo_arg[len - 1] == '"')
				write(1, echo_arg, len - 1);
			else
				write(1, echo_arg, len);
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