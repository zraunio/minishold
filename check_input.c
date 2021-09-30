/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 16:53:11 by ehelmine          #+#    #+#             */
/*   Updated: 2021/09/30 14:50:26 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*check_echo_flags_and_skip_whitespaces(char *input, t_shell *data,
		int i)
{
	while (ft_isspace(input[0]) && input[0] != '\0')
		input++;
	input += 4;
	if (input[0] == '\0')
		return (NULL);
	i = 0;
	while (ft_isspace(input[i]) && input[i] != '\0')
		i++;
	while (input[i] == '-' && input[i + 1] == 'n')
	{
		input += i + 1;
		i = 0;
		while (input[0] == 'n' && input[0] != '\0')
			input++;
		if (input[0] == '\0' || ft_isspace(input[0]))
		{
			data->n_flag = 1;
			if (input[0] == '\0')
				return (NULL);
			while (ft_isspace(input[0]) && input[0] != '\0')
				input++;
		}
	}
	return (input + i);
}

static void	change_input_row(char **buf_arr, int y, int x, char quote)
{
	int		start;
	char	*begin;
	char	*middle;
	char	*end;
	char	*tmp;

	start = x;
	while (buf_arr[y][x] != quote && buf_arr[y][x] != '\0')
		x++;
	if (start - 1 < 0)
		begin = ft_strdup("");
	else
		begin = ft_strndup(buf_arr[y], start - 1);
	if (x - start < 0)
		middle = ft_strdup("");
	else
		middle = ft_strsub(buf_arr[y], start, x - start);
	end = ft_strdup(buf_arr[y] + x + 1);
	tmp = ft_strjoin_three(begin, middle, end);
	ft_memset((void *)buf_arr[y], 0, ft_strlen(buf_arr[y]));
	ft_strcpy(buf_arr[y], tmp);
	free_two((void *)&begin, (void *)&middle);
	free_two((void *)&end, (void *)&tmp);
}

static int	check_command_with_quotes(char *command, t_shell *data)
{
	char	**arr;
	char	*check;

	arr = (char **)malloc(sizeof(char *) * 2);
	arr[0] = NULL;
	if (command[0] == '"')
		arr[0] = return_string_before_given_char(command + 1, '"');
	else if (command[0] == '\'')
		arr[0] = return_string_before_given_char(command + 1, '\'');
	arr[1] = NULL;
	if (ft_strequ("cd", arr[0]) || ft_strequ("exit", arr[0])
		|| ft_strequ("env", arr[0]) || ft_strequ("unsetenv", arr[0])
		|| ft_strequ("setenv", arr[0]) || ft_strequ("echo", arr[0]))
	{
		free_arr((void *)&arr);
		return (1);
	}
	check = check_if_exec_with_quotes(arr[0], data);
	free(arr);
	if (check == NULL)
		return (0);
	ft_memdel((void *)&check);
	return (1);
}

static void	check_input_array_loop(char **buf_arr, int x, int y)
{
	char	quote;

	quote = 'a';
	while (buf_arr[y] != NULL)
	{
		while (buf_arr[y][x] != '\0')
		{
			if (buf_arr[y][x] == '"' || buf_arr[y][x] == '\'')
			{
				quote = buf_arr[y][x++];
				change_input_row(buf_arr, y, x, quote);
				quote = 'a';
				x = -1;
			}
			x++;
		}
		y++;
		x = 0;
	}	
}

int	check_input_array(char **buf_arr, int y, int x, t_shell *data)
{
	char	*check;

	if (buf_arr[0][0] == '"' || buf_arr[0][0] == '\'')
	{
		if (check_command_with_quotes(buf_arr[0], data) == 0)
			return (0);
	}
	check = return_string_before_whitespace(buf_arr[0]);
	if (check == NULL)
		check = ft_strdup(buf_arr[0]);
	if (ft_strequ("echo", check) == 1)
	{
		ft_memdel((void *)&check);
		return (1);
	}
	ft_memdel((void *)&check);
	check_input_array_loop(buf_arr, x, y);
	return (1);
}
