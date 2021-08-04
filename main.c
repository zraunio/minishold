/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:14:45 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/04 16:42:53 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	ft_putstr("myshell> ");
	read_input();
	return (0);
}