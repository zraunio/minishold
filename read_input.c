/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:02:38 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/01 17:55:41 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	loop_more_quotes(char *buf, int num_of_quotes, t_shell *data)
{
	char *extra_buf;

	extra_buf = (char *)malloc(sizeof(char) * 500);
	if (buf == NULL)
		exit (1);
	while (num_of_quotes % 2 != 0)
	{
		if (data->quote == 2)
			write(1, "dquote> ", 8);
		else
			write(1, "quote> ", 7);
		ft_memset((void *)extra_buf, 0, 500);
		buf[0] = '\n';
		loop_input_to_string(buf + 1);
		ft_strcat(buf, extra_buf);
		num_of_quotes = check_amount_of_quotes(buf, data);
		ft_printf("num_of_quotes %i\n", num_of_quotes);
	}
	free(extra_buf);
}

int	check_quotes_for_input(char *buf, t_shell *data)
{
	int	i;
	int	d_q;
	int	s_q;

	i = 0;
	d_q = 0;
	s_q = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '"' && buf[i - 1] != '\\' && data->quote != 1)
		{
			d_q++;
			data->quote = 2;
		}
		else if (buf[i] == '\'' && buf[i - 1] != '\\' && data->quote != 2)
		{
			s_q++;
			data->quote = 1;
		}
		i++;
	}
	if (data->quote == 2)
		return (d_q);
	if (data->quote == 1)
		return (s_q);
	return (0);
}

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
	while (x > 0)
	{
		buf[i++] = c;
		if (c == '\n')
			break ;
		x = read(0, &c, 1);
	}
	buf[i - 1] = '\0';
}

void	set_buf_and_get_input(char *buf, t_shell *data)
{
	int	num_of_quotes;
	
	ft_memset((void *)buf, 0, 500);
	loop_input_to_string(buf);
	data->quote = 0;
	num_of_quotes = check_quotes_for_input(buf, data);
	ft_printf("dataquote %i num %i\n", data->quote, num_of_quotes);
	if (num_of_quotes % 2 != 0 && num_of_quotes != 0)
		loop_more_quotes(buf, num_of_quotes, data);
}

void	fork_and_child(char **path_array, t_shell *data)
{
	char	*buf;
	char	**buf_arr;
	pid_t	child_pid;
	int		child_status;
	pid_t	tpid;
	int		i;
	char	*tmp;
	char	*arg_for_ex;
	char	*argv[] = {NULL, NULL, NULL};

	i = 0;
	tmp = NULL;
	buf = (char *)malloc(sizeof(char) * 500);
	if (buf == NULL)
		exit (1);
	while (1)
	{
		set_buf_and_get_input(buf, data);
		buf_arr = split_input_to_array(buf);
		if (buf_arr != NULL)
		{
			tmp = check_if_built_in(buf_arr);
			if (tmp != NULL)
			{
				execute_built_in(tmp, data, buf_arr);
				free(tmp);
				tmp = NULL;
			}
			else
				tmp = check_if_executable(buf_arr, path_array);
//			ft_printf("what is here |%s|\n", tmp);
			if (tmp != NULL)
			{
				child_pid = fork();
				arg_for_ex = ft_strchr(buf_arr[0], ' ');
				if (arg_for_ex != NULL)
				{
					arg_for_ex++;
					argv[1] = arg_for_ex;
				}
				else
					argv[1] = NULL;
				if (child_pid == 0)
				{
					argv[0] = tmp;
					if (execve(tmp, argv, data->copy_of_environ) == -1)
					{
				//  		perror("childpid 0");
					}
					if (path_array != NULL)
					{
						while (path_array[i] != NULL)
							free((void *)path_array[i++]);
						free(path_array);
					}
				}
				else if (child_pid < 0)
				{
				//	perror("childpid <0");
				}
				else
				{
				//	ft_printf("child %i\n", child_pid);
					tpid = waitpid(child_pid, &child_status, 0);
					while (tpid > 0)
						tpid = waitpid(child_pid, &child_status, 0);
				}
			}
			i = 0;
			while (buf_arr[i] != NULL)
				free(buf_arr[i++]);
			free(buf_arr);
			free(tmp);
			tmp = NULL;
		}
		ft_putstr("myshell> ");
	}
}
