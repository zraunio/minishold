/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:14:45 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/10 12:18:59 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// ps aux | grep 21sh
// killall 21sh

// CHECK WHAT FORK RETURNS..
// • You must program a mini UNIX command interpreter.
// • This interpreter must display a prompt (a simple "$> " for example) and
// wait till you type a command line, validated by pressing enter.
// • The prompt is shown again only once the command has been completely
// executed.
// • The command lines are simple, no pipes, no redirections or any other
// advanced functions.
// • The executable are those you can find in the paths indicated in the
// PATH variable.
// • In cases where the executable cannot be found, it has to show an error
// message and display the prompt again.
// • You must manage the errors without using errno, by displaying
// a message adapted to the error output.
// • You must deal correctly with the PATH and the environment (copy of
// system char **environ).
// • You must implement a series of builtins: echo, cd, setenv, unsetenv,
// env, exit.
// • You can choose as a reference whatever shell you prefer.
// • You must manage expansions $ and ˜

/*
** Extern char **environ holds for example $PATH variables. In a loop we find
** where PATH is, and then we take all $PATH variables to path_array, so
** we can use those later to see if input is an executable and if it can
** be found with the paths (for example command ls would be found in /bin/).
*/

char	**get_paths_to_array(char **environ)
{
	int i;
	char **path_array;

	i = 0;
	while (environ[i] != NULL)
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

/*
** Here we get a copy of extern char **environ.
*/

char	**get_copy_of_environment_variables()
{
	extern char	**environ;
	int			num_of_vars;
	char		**path_array;
	char		**copy_of_environ;
	int			i;
	
	num_of_vars = 0;
	i = 0;
	path_array = NULL;
	while (environ[num_of_vars] != NULL)
		num_of_vars++;
	copy_of_environ = (char **)malloc(sizeof(char *) * (num_of_vars + 1));
	if (copy_of_environ == NULL)
		exit(1);
	while (i < num_of_vars)
	{
		copy_of_environ[i] = ft_strdup(environ[i]);
		i++;
	}
	copy_of_environ[i] = NULL;
	return (copy_of_environ);
}

/*
** In main we create two arrays by calling other functions: we get
** copy of extern char **environ and all $PATH variables in array.
** After that we write myshell> as a new command line to our shell,
** and we continue to other function.
*/

int main() 
{
	char **copy_of_environ;
	char **path_array;
	
	copy_of_environ = get_copy_of_environment_variables();
	// REMEMBER TO FREE COPY OF ENVIRON
	path_array = get_paths_to_array(copy_of_environ);
	// REMEMBER TO FREE PATH ARRAY
	write(1, "myshell> ", 9);
	fork_and_child(path_array, copy_of_environ);
	return (0);
}