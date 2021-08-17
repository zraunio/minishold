/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:02:38 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/17 17:49:51 by ehelmine         ###   ########.fr       */
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
	while (x > 0)
	{
		buf[i++] = c;
		if (c == '\n')
			break ;
		x = read(0, &c, 1);
	}
	buf[i - 1] = '\0';
}

void	set_buf_and_get_input(char *buf)
{
	ft_memset((void *)buf, 0, 500);
	loop_input_to_string(buf);
}

void	fork_and_child(char **path_array, char **copy_of_environ)
{
	char	*buf;
	char	**buf_arr;
	pid_t	child_pid;
	int		child_status;
	pid_t	tpid;
	int		i;
	char	*tmp;
	char	*argv[] = {NULL, NULL, NULL};

	i = 0;
	tmp = NULL;
	buf = (char *)malloc(sizeof(char) * 500);
	if (buf == NULL)
		exit (1);
	while (1)
	{
		set_buf_and_get_input(buf);
		buf_arr = split_input_to_array(buf);
		if (buf_arr != NULL)
		{
			tmp = check_if_built_in(buf_arr);
			if (tmp != NULL)
			{
				execute_built_in(tmp, copy_of_environ, buf_arr);
				free(tmp);
				tmp = NULL;
			}
			else
				tmp = check_if_executable(buf_arr, path_array);
			if (tmp != NULL)
			{
				child_pid = fork();
				if (buf_arr[1] != NULL)
					argv[1] = buf_arr[1];
				else
					argv[1] = NULL;
				if (child_pid == 0)
				{
					argv[0] = tmp;
					if (execve(tmp, argv, copy_of_environ) == -1)
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
		}
		ft_putstr("myshell> ");
	}
}
