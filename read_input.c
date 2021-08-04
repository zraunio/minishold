/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:02:38 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/04 16:58:45 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
** Read standard input to buffer (which is always size 500) character
** by character. If it hits a newline, break the loop,
** put null character in the end and return.
*/

void	loop_input_to_string(char *buf)
{
	int i;
	int x;
	char c;
	
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

void	read_input()
{
	char *buf;
	char **buf_arr;
	pid_t child_pid;
	int child_status;
	pid_t tpid;
	char **path_array;
	int i;
	struct stat buff;
	char *tmp;
	char *argv[] = {"ls", NULL, NULL};
 	char *my_env_args[] = { "PATH=/bin/", "USER=me", NULL };

	path_array = NULL;
	path_array = get_paths_to_array();
	i = 0;
	tmp = NULL;
	buf = (char *)malloc(sizeof(char) * 500);
	if (buf == NULL)
		exit (1);
	while (1)
	{
		ft_memset((void *)buf, 0, 500);
		loop_input_to_string(buf);
		split_input_to_array(buf);
		buf_arr = ft_strsplit(buf, ' ');
		if (buf_arr == NULL)
			exit(1);
		if (buf[0] == 'e')
		{
			if (ft_strcmp(buf, "exit") == 0)
				exit (0);
		}
		else if (ft_strcmp(buf_arr[0], "ls") == 0)
		{
			child_pid = fork();
			if (buf_arr[1] != '\0')
				argv[1] = buf_arr[1];
			else
				argv[1] = NULL;
			if(child_pid == 0)
			{
				i = 0;
				if (tmp != NULL)
					free(tmp);
				tmp = NULL;
				tmp = ft_strdup(buf_arr[0]);
				free(buf_arr[0]);
				buf_arr[0] = ft_strjoin("/", tmp);
				free(tmp);
				while (path_array[i] != NULL)
				{
					tmp = ft_strjoin(path_array[i], buf_arr[0]);
					if (lstat(tmp, &buff) == 0)
						break ;
					free(tmp);
					i++;
				}
				if (execve(tmp, argv, my_env_args) == -1)
			  		perror("childpid 0");
				if (path_array != NULL)
				{
					while (path_array[i] != '\0')
					{
						ft_putstr(path_array[i]);
						free((void*)path_array[i++]);
						ft_putstr("\n");
					}
					free(path_array);
				}
			}
			else if (child_pid < 0)
				perror("childpid <0");
			else
			{
				tpid = waitpid(child_pid, &child_status, 0);
				while (tpid > 0)
					tpid = waitpid(child_pid, &child_status, 0);

			}
		}
		else
		{
			if (buf[0] != '\n')
			{
				ft_putstr(buf);
				write(1, "\n", 1);
			}
		}
		i = 0;
		while (buf_arr[i] != '\0')
			free(buf_arr[i++]);
		free(buf_arr);
		ft_putstr("myshell> ");
	}
}