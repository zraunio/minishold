/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:02:38 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/05 18:01:33 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
** Read standard input to buffer (which is always size 500) character
** by character. If it hits a newline, break the loop,
** put null character in the end and return.
*/

char	*return_string_before_given_character(char *str, char c)
{
	int i;
	char *new_str;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			new_str = ft_strndup(str, i);
			return (new_str);
		}
		i++;
	}
	return (NULL);
}

char	*check_input_array(char **buf_arr, char **path_array)
{
	char *tmp;
	char *tmp2;
	int i;
	struct stat buff;
	char *if_exec;

	i = 0;
	if_exec = return_string_before_given_character(buf_arr[0], ' ');
	if (if_exec == NULL)
		if_exec = ft_strdup(buf_arr[0]);
	while (path_array[i] != NULL)
	{
		tmp = ft_strjoin(path_array[i], "/");
		tmp2 = ft_strjoin(tmp, if_exec);
//		ft_printf("tmp2 |%s|\n", tmp2);
		if (lstat(tmp2, &buff) == 0)
		{
			free(if_exec);
			free(tmp);
			return (tmp2);
		}
		free(tmp);
		free(tmp2);
		i++;
	}
	free(if_exec);
	ft_printf("zsh: command not found: |%s|\n", buf_arr[0]);
	return (NULL);
}

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

void	get_input(char *buf)
{
	ft_memset((void *)buf, 0, 500);
	loop_input_to_string(buf);
}

void	fork_and_child(char **path_array, char **copy_of_environ)
{
	char *buf;
	char **buf_arr;
	pid_t child_pid;
	int child_status;
	pid_t tpid;
	int i;
	char *tmp;
	char *argv[] = {NULL, NULL, NULL};

	i = 0;
	tmp = NULL;
	buf = (char *)malloc(sizeof(char) * 500);
	if (buf == NULL)
		exit (1);
	while (1)
	{
		get_input(buf);
		buf_arr = split_input_to_array(buf);
		if (buf_arr != NULL)
		{
			tmp = check_input_array(buf_arr, path_array);
			if (tmp != NULL)
			{
				ft_printf("WHAT IS IT |%s|\n", tmp);
				if (tmp[0] == 'e')
				{
					if (ft_strcmp(tmp, "exit") == 0)
						exit (0);
				}
				else
				{
					ft_putstr("here");
					child_pid = fork();
					if (buf_arr[1] != '\0')
						argv[1] = buf_arr[1];
					else
						argv[1] = NULL;
					if(child_pid == 0)
					{
						argv[0] = tmp;
						if (execve(tmp, argv, copy_of_environ) == -1)
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
						ft_printf("child %i\n", child_pid);
						tpid = waitpid(child_pid, &child_status, 0);
						while (tpid > 0)
							tpid = waitpid(child_pid, &child_status, 0);
	
					}
				}
			}
			i = 0;
			while (buf_arr[i] != '\0')
				free(buf_arr[i++]);
			free(buf_arr);
		}
		ft_putstr("myshell> ");
	}
}