/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:02:38 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/07 13:45:41 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*skip_all_whitespaces_and_dup_new_str(char *str)
{
	int		i;
	int		space_len;
	char	*new_str;
	char	*begin;
	char	*end;

	i = 0;
	space_len = 0;
	new_str = ft_strdup(str);
	while (new_str[i] != '\0')
	{
		while (ft_isspace(new_str[i + space_len]) &&
			new_str[i + space_len] != '\0')
			space_len++;
		if (new_str[i + space_len] == '\0' && space_len > 1)
		{
			free(new_str);
			new_str = ft_strndup(new_str, i);
			return (new_str);
		}
		if (i == 0 && space_len >= 1)
		{
			free(new_str);
			new_str = ft_strdup(new_str + space_len);
			space_len = 0;
			i = -1;
		}
		else if (space_len > 1)
		{
			begin = ft_strndup(new_str, i);
			end = ft_strdup(new_str + space_len + i - 1);
			free(new_str);
			ft_printf("begin |%s| end |%s|\n", begin, end);
			new_str = ft_strjoin(begin, end);
			free_two((void *)begin, (void *)end);
			space_len = 0;
			i = -1;
		}
		space_len = 0;
		i++;
	}
	return (new_str);
}

void	fork_and_child(t_shell *data, char *executable, char **buf_arr)
{
	pid_t	child_pid;
	pid_t	tpid;
	int		child_status;
	int		i;
	char	*args;
	char	**arg_arr;

	i = 0;
	i += ft_strlen(data->original_exec);
	args = skip_all_whitespaces_and_dup_new_str(*(buf_arr)+ i);
	ft_printf("new str |%s|\n", args);
	child_pid = fork();
	arg_arr = NULL;
	if (args != NULL)
		arg_arr = ft_strsplit(args, ' ');
	if (child_pid == 0)
	{
		arg_arr = add_exec_to_arr(arg_arr, executable);
		if (execve(executable, arg_arr, data->copy_of_environ) == -1)
		{
	//  		perror("childpid 0");
		}
	}
	else if (child_pid < 0)
	{
	//	perror("childpid <0");
	}
	else
	{
		tpid = waitpid(child_pid, &child_status, 0);
		while (tpid > 0)
			tpid = waitpid(child_pid, &child_status, 0);
	}
	if (arg_arr != NULL)
		free_arr((void **)arg_arr);
	if (data->original_exec != NULL)
		free(data->original_exec);
	if (args != NULL)
		free(args);
	free(executable);
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
	char	quote;
	
	ft_memset((void *)buf, 0, 500);
	loop_input_to_string(buf);
	quote = check_quotes_for_input(buf);
	if (quote != 'a')
		loop_more_quotes(buf, quote);
}

void	while_loop_input(t_shell *data)
{
	char	*buf;
	char	**buf_arr;
	char	*tmp;

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
			check_input_array(buf_arr);
			tmp = check_if_built_in(buf_arr);
			if (tmp != NULL)
			{
				execute_built_in(tmp, data, buf_arr);
				ft_memdel((void **)tmp);
			}
			else
				tmp = check_if_executable(buf_arr, data);
			if (tmp != NULL)
				fork_and_child(data, tmp, buf_arr);
			free_arr((void *)buf_arr);
		}
		ft_putstr("minishell> ");
	}
}
