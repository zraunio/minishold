/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:15:11 by ehelmine          #+#    #+#             */
/*   Updated: 2021/08/30 21:46:02 by ehelmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_amount_of_quotes(char *args, t_shell *data)
{
	int	i;
	int	single_q;
	int	double_q;

	i = 0;
	double_q = 0;
	single_q = 0;
	while (args[i] != '\0')
	{
		if (args[i] == '"' && single_q == 0 && data->quote != 1)
		{
			double_q++;
			data->quote = 2;
		}
		else if (args[i] == '\'' && double_q == 0 && data->quote != 2)
		{
			single_q++;
			data->quote = 1;
		}
		i++;
	}
	if (double_q > 0)
		return (double_q);
	return (single_q);
}

/*
** If input only holds for example --  echo "hello $path -- and doesn't
** have the last double quote, we output dquote> and wait & read, until we
** get the second double quote from the user.
*/

void	loop_double_quotes(char *args, int am_of_quotes, t_shell *data)
{
	char	*buf;
	char	**buf_arr;

	buf = (char *)malloc(sizeof(char) * 500);
	if (buf == NULL)
		exit (1);
	while (am_of_quotes % 2 != 0)
	{
		if (data->quote == 2)
			write(1, "dquote> ", 8);
		else
			write(1, "quote> ", 7);
		ft_memset((void *)buf, 0, 500);
		buf[0] = '\n';
		loop_input_to_string(buf + 1);
		buf_arr = split_input_to_array(buf);
		ft_strcat(args, buf_arr[0]);
		am_of_quotes = check_amount_of_quotes(args, data);
	}
	free(buf);
}
