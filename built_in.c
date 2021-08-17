/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:57:03 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/17 09:56:33 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
** echo needs to also write into FDs, more detail needed
** could perhaps be a (char *input, ...) type of function?
*/

void	my_echo(char *input)
{
	int i;
	char *echo_arg;
	
	i = 0;
	while (input[i] == ' ')
		i++;
	input += i;
	echo_arg = ft_strstr(input, " ");
	if (echo_arg != NULL)
	{
		echo_arg++;
		if (echo_arg[0] != '\0' && (echo_arg[0] != ';' || echo_arg[0] != '|'))
			ft_putstr(echo_arg);
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
		my_echo(args[0]);
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
