/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:14:45 by ehelmine          #+#    #+#             */
/*   Updated: 2021/07/29 14:58:00 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "libft/includes/libft.h"

// ps aux | grep 21sh
// killall 21sh

// CHECK WHAT FORK RETURNS..
// • You must program a mini UNIX command interpreter.
// • This interpreter must display a prompt (a simple "$> " for example) and wait till
// you type a command line, validated by pressing enter.
// • The prompt is shown again only once the command has been completely executed.
// • The command lines are simple, no pipes, no redirections or any other advanced
// functions.
// • The executable are those you can find in the paths indicated in the PATH variable.
// • In cases where the executable cannot be found, it has to show an error message and
// display the prompt again.
// • You must manage the errors without using errno, by displaying a message adapted
// to the error output.
// • You must deal correctly with the PATH and the environment (copy of system char
// **environ).
// • You must implement a series of builtins: echo, cd, setenv, unsetenv, env, exit.
// • You can choose as a reference whatever shell you prefer.
// • You must manage expansions $ and ˜

char	**get_paths_to_array()
{
	extern char **environ;
	int i;
	char **path_array;

	i = 0;
	while (environ[i] != '\0')
	{
		if (environ[i][0] == 'P')
		{
			if (environ[i][1] == 'A' && environ[i][2] == 'T' && environ[i][3]
				== 'H' && environ[i][5] != '\0')
			{
				path_array = ft_strsplit(*(environ + i) + 5, ':');
				if (path_array != NULL)
					return (path_array);
				exit (1);
			}
		}
		i++;
	}
	return (NULL);
}

int main() 
{
	char buf[100];
	char *argv[] = {"ls", NULL, NULL};
 	char *my_env_args[] = { "PATH=/bin", "USER=me", NULL };
	char c;
	int x;
	int i;
	pid_t child_pid;
	int child_status;
	pid_t tpid;
	char **arr;
	char **path_array;

	path_array = NULL;
	path_array = get_paths_to_array();
	i = 0;
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
	ft_putstr("myshell> ");
	while (1)
	{
		ft_memset((void *)buf, 0, 100);
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
		arr = ft_strsplit(buf, ' ');
		if (arr == NULL)
			exit(1);
		if (buf[0] == 'e')
		{
			if (ft_strcmp(buf, "exit") == 0)
				exit (0);
		}
		else if (ft_strcmp(arr[0], "ls") == 0)
		{
			child_pid = fork();
			if (arr[1] != '\0')
				argv[1] = arr[1];
			if(child_pid == 0)
			{
			  if (execve("/bin/ls", argv, my_env_args) == -1)
			  	perror("childpid 0");
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
		while (arr[i] != '\0')
			free(arr[i++]);
		free(arr);
		ft_putstr("myshell> ");
	}
	return (0);
}