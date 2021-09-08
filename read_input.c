/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:02:38 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/08 16:53:42 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
** Read input until it hits newline.
*/

void	loop_input_to_string(char *buf)
{
	int		i;
	int		x;
	char	c;

	i = 0;
	x = read(0, &c, 1);
	if (c == '\0')
	{
		write(1, "\n", 1);
		exit (1);
	}
	while (x > 0)
	{
		buf[i++] = c;
		if (c == '\n')
			break ;
		x = read(0, &c, 1);
	}
	buf[i - 1] = '\0';
}

char	*set_buf_and_get_input(void)
{
	char	quote;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * 500);
	check_if_null((void *)buf);
	ft_memset((void *)buf, 0, 500);
	loop_input_to_string(buf);
	quote = check_quotes_for_input(buf);
	if (quote != 'a')
		loop_more_quotes(buf, quote);
	return (buf);
}

void	work_with_input(t_shell *data, char **buf_arr)
{
	char	*tmp;

	tmp = NULL;
	check_input_array(buf_arr, 0, 0);
	tmp = check_if_built_in(buf_arr);
	if (tmp != NULL)
	{
		execute_built_in(tmp, data, buf_arr);
		free(tmp);
		tmp = NULL;
	}
	else
		tmp = check_if_executable(buf_arr, data, 0);
	if (tmp != NULL)
		fork_and_child(data, tmp, buf_arr);
	free_arr((void **)buf_arr);
}

void	while_loop_input(t_shell *data)
{
	char	*buf;
	char	**buf_arr;

	while (1)
	{
		buf = set_buf_and_get_input();
		buf_arr = split_input_to_array(buf, 0, 0, 0);
		if (buf_arr != NULL)
			work_with_input(data, buf_arr);
		free(buf);
		ft_putstr("minishell> ");
	}
}
