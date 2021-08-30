/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:14:45 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/30 14:56:18 by ehelmine         ###   ########.fr       */
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

char	**get_paths_to_array(t_shell *data)
{
	int		i;
	char	**path_array;

	i = 0;
	while (data->copy_of_environ[i] != NULL)
	{
		if (data->copy_of_environ[i][0] == 'P')
		{
			if (data->copy_of_environ[i][1] == 'A'
				&& data->copy_of_environ[i][2] == 'T'
				&& data->copy_of_environ[i][3]
				== 'H' && data->copy_of_environ[i][5] != '\0')
			{
				path_array = ft_strsplit(*(data->copy_of_environ + i) + 5,
						':');
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
** Here we get a copy of extern char **environ to our own array.
** Later it needs to be freed < keywords malloc free >.
** Also we set prev_dirs array to NULL.
*/

void	get_copy_of_environment_variables(t_shell *data)
{
	extern char	**environ;
	int			num_of_vars;
	char		**path_array;
	int			i;

	num_of_vars = 0;
	i = 0;
	path_array = NULL;
	while (environ[num_of_vars] != NULL)
		num_of_vars++;
	data->copy_of_environ = (char **)malloc(sizeof(char *) * (num_of_vars + 1));
	if (data->copy_of_environ == NULL)
		exit(1);
	while (i < num_of_vars)
	{
		data->copy_of_environ[i] = ft_strdup(environ[i]);
		i++;
	}
	data->copy_of_environ[num_of_vars] = NULL;
	data->num_of_variables = num_of_vars;
	data->prev_dirs = NULL;
}

/*
** In main we create two arrays by calling other functions: we get
** copy of extern char **environ and all $PATH variables in array.
** After that we write myshell> as a new command line to our shell,
** and we continue to other function.
*/

int	main(void)
{
	char	**path_array;
	t_shell	data;

	get_copy_of_environment_variables(&data);
	// REMEMBER TO FREE COPY OF ENVIRON
	path_array = get_paths_to_array(&data);
	// REMEMBER TO FREE PATH ARRAY
	write(1, "myshell> ", 9);
	fork_and_child(path_array, &data);
	return (0);
}
