/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:14:45 by ehelmine          #+#    #+#             */
/*   Updated: 2021/07/28 17:13:51 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "libft/includes/libft.h"

// ps aux | grep 21sh
// killall 21sh

// CHECK WHAT FORK RETURNS..

int main() 
{
	char buf[100];
	char *argv[] = {"ls", NULL, NULL};
  char *envp[] = {NULL };
	char c;
	int x;
	int i;
	pid_t child_pid;
	int child_status;
	pid_t tpid;
	char **arr;

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
			  if (execve("/bin/ls", argv, envp) == -1)
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
		ft_putstr("myshell> ");
	}
	return (0);
}