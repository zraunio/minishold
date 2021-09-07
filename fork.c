/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:31:01 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/07 15:57:29 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	execve_command(t_shell *data, char **arg_arr,
		char *executable)
{
	pid_t	tpid;
	pid_t	child_pid;
	int		child_status;

	child_pid = fork();
	if (child_pid == 0)
	{
		arg_arr = add_exec_to_arr(arg_arr, executable);
		if (execve(executable, arg_arr, data->copy_of_environ) == -1)
			ft_printf("chilpid 0");
	}
	else if (child_pid < 0)
		ft_printf("childpid <0");
	else
	{
		tpid = waitpid(child_pid, &child_status, 0);
		while (tpid > 0)
			tpid = waitpid(child_pid, &child_status, 0);
	}
}

char	*skip_whitespace_begin_and_end(char *s)
{
	int		y;
	int		i;
	char	*new_str;
	int		len;

	len = ft_strlen(s);
	if (s[0] == '\0')
		return (ft_strnew(0));
	i = 0;
	while (ft_isspace(s[i]) && s[i] != '\0')
		i++;
	while (ft_isspace(s[len - 1]) && i != len)
		len--;
	new_str = (char *)malloc(sizeof(char) * (len - i + 1));
	if (new_str == NULL)
		return (NULL);
	y = 0;
	while (i < len && len > 0)
		new_str[y++] = s[i++];
	new_str[y] = '\0';
	return (new_str);
}	

char	*allocate_arg(char *new_str, int i, int space_len)
{
	char	*begin;
	char	*end;
	char	*ret_str;

	begin = ft_strndup(new_str, i);
	end = ft_strdup(new_str + i + space_len);
	free(new_str);
	ret_str = ft_strjoin_three(begin, " ", end);
	free_two((void *)begin, (void *)end);
	return (ret_str);
}

char	*skip_all_whitespaces_and_dup_new_str(char *str)
{
	int		i;
	int		space_len;
	char	*new_str;
	char	*tmp;

	i = 0;
	space_len = 0;
	new_str = skip_whitespace_begin_and_end(str);
	tmp = NULL;
	while (new_str[i] != '\0')
	{
		space_len = 0;
		while (ft_isspace(new_str[i + space_len])
			&& new_str[i + space_len] != '\0')
			space_len++;
		if (space_len > 1)
		{
			new_str = allocate_arg(new_str, i, space_len);
			i = -1;
		}
		i++;
	}
	return (new_str);
}

void	fork_and_child(t_shell *data, char *executable, char **buf_arr)
{
	int		i;
	char	*args;
	char	**arg_arr;

	i = 0;
	i += ft_strlen(data->original_exec);
	data->original_exec = NULL;
	args = skip_all_whitespaces_and_dup_new_str(*(buf_arr) + i);
	arg_arr = NULL;
	if (args != NULL)
		arg_arr = ft_strsplit(args, ' ');
	execve_command(data, arg_arr, executable);
	free_fork_and_child(data, executable, args, arg_arr);
}
