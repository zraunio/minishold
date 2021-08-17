/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:02:38 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/17 17:26:55 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*return_string_before_given_character(char *str, char c)
{
	int		i;
	char	*new_str;

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

char	*check_if_built_in(char **buf_arr)
{
	int		i;
	char	*built_ins[] = {"echo", "cd", "setenv", "unsetenv", "env", "exit"};
	char	*if_built_in;

	i = 0;
	if_built_in = return_string_before_given_character(buf_arr[0], ' ');
	if (if_built_in == NULL)
		if_built_in = ft_strdup(buf_arr[0]);
	while (i < 6)
	{
		if (ft_strcmp(built_ins[i], if_built_in) == 0)
			return (if_built_in);
		i++;
	}
	free(if_built_in);
	return (NULL);
}

char	*check_if_executable(char **buf_arr, char **path_array)
{
	char		*tmp;
	char		*tmp2;
	int			i;
	struct stat	buff;
	char		*if_exec;

	i = 0;
	if_exec = return_string_before_given_character(buf_arr[0], ' ');
	if (if_exec == NULL)
		if_exec = ft_strdup(buf_arr[0]);
	while (path_array[i] != NULL)
	{
		tmp = ft_strjoin(path_array[i], "/");
		tmp2 = ft_strjoin(tmp, if_exec);
		if (lstat(tmp2, &buff) == 0)
		{
			free_two(if_exec, tmp);
			return (tmp2);
		}
		free_two(tmp, tmp2);
		i++;
	}
	ft_printf("zsh: command not found: |%s|\n", if_exec);
	free(if_exec);
	return (NULL);
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
