/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:57:03 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/25 18:35:26 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	my_echo(char *input, t_shell *data)
{
	int		i;
	char	*echo_arg;
	int		n_flag;
	
	i = 0;
	n_flag = 0;
	while (input[i] == ' ')
		i++;
	input += i;
	echo_arg = ft_strstr(input, " ");
	if (echo_arg[1] == '-' && echo_arg[2] == 'n')
	{
		if (echo_arg[3] == '\0')
			return ;
		if (echo_arg[3] == ' ')
		{
			n_flag = 1;
			echo_arg = ft_strstr(input + 5, " ");
		}
	}
	if (echo_arg != NULL)
	{
		i = 0;
		while (echo_arg[i] != '\0')
		{
			while (echo_arg[i] == ' ')
				i++;
			if (echo_arg[i] == '$')
				echo_arg = print_dollar(data->copy_of_environ, echo_arg + i + 1);
			else if (echo_arg[i] == '"')
				echo_arg = print_double_quotes(echo_arg + i + 1, data->copy_of_environ);
			else if (echo_arg[i] != '|' || echo_arg[i] != ';')
				echo_arg = print_text_after_pipe_or_semicolon(echo_arg + i);
			i = 0;
		}
	}
	if (!n_flag)
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

/*
** If input only holds for example --  echo "hello $path -- and doesn't
** have the last double quote, we output dquote> and wait & read, until we
** get the second double quote from the user.
*/

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

/*
** We know now which built_in we are gonna execute, so here we are going
** to check which one it was based on the first and second character of
** the string that contains that built_in (char *built_in).
** Based on that then we are going to call specific function to do what we
** want.
*/

void	execute_built_in(char *built_in, t_shell *data, char **args)
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
		my_echo(args[0], data);
	}
	else if (built_in[0] == 's')
		set_environment_variable(data, args[0]);
	else if (built_in[0] == 'u')
		unset_environment_variable(data, args[0]);
	else
		ft_putarr(data->copy_of_environ);
}