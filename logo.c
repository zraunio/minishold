/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 15:29:23 by zraunio           #+#    #+#             */
/*   Updated: 2021/08/17 10:11:52 by zraunio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	logo4(void)
{
	ft_putendl("EEEEEEE lll lll                   lll lll                   hh                hh");
	ft_putendl("EE      lll lll   aa aa      eee  lll lll   aa aa      eee  hh           eee  hh");
	ft_putendl("EEEEE   lll lll  aa aaa    ee   e lll lll  aa aaa    ee   e hhhhhh     ee   e hhhhhh");
	ft_putendl("EE      lll lll aa  aaa    eeeee  lll lll aa  aaa    eeeee  hh   hh    eeeee  hh   hh");
	ft_putendl("EEEEEEE lll lll  aaa aa     eeeee lll lll  aaa aa     eeeee hh   hh     eeeee hh   hh");
	ft_putchar('\n');
	ft_putendl("				~ minishell project");
}

static void	logo3(void)
{
	ft_putendl(" +-+-+-+-+-+ +-+-+ +-+-+-+-+");
	ft_putendl(" |w|i|l|l|e| |t|o| |l|i|v|e|");
	ft_putendl(" +-+-+-+-+-+ +-+-+ +-+-+-+-+");
	ft_putchar('\n');
	ft_putendl("				~ minishell project");
}

static void	logo2(void)
{
	ft_putendl("                           .        . . ");
	ft_putendl("          o         o      |        | | ");
	ft_putendl(".--.--.   .  .--.   .  .--.|--. .-. | | ");
	ft_putendl("|  |  |   |  |  |   |  `--.|  |(.-' | | ");
	ft_putendl("'  '  `--' `-'  `--' `-`--''  `-`--'`-`-");
	ft_putendl("");
	ft_putendl("                              ~ ehelmine ~");
	ft_putendl("                              ~  wvaara  ~");
	ft_putendl("                              ~  zraunio ~");
}

static void	logo1(void)
{
	ft_putendl(" ____        _____       ____        ______");
	ft_putendl("/\\  _`\\     /\\  __`\\    /\\  _`\\     /\\__  _\\");
	ft_putendl("\\ \\ \\L\\ \\   \\ \\ \\/\\ \\   \\ \\ \\L\\ \\   \\/_/\\ \\/");
	ft_putendl(" \\ \\ ,  /    \\ \\ \\ \\ \\   \\ \\ ,  /      \\ \\ \\");
	ft_putendl("  \\ \\ \\ \\     \\ \\ \\_\\ \\   \\ \\ \\ \\       \\_\\ \\__ ");
	ft_putendl("   \\ \\_\\ \\_\\   \\ \\_____\\   \\ \\_\\ \\_\\    /\\_____\\");
	 ft_putendl("    \\/_/\\/ /    \\/_____/    \\/_/\\/ /    \\/_____/");
	ft_putchar('\n');
	ft_putendl("				~ minishell project");
}

void	set_logo(t_shell *shell)
{
	srand(time(NULL));
	shell->logo = rand() % 5;
	if (shell->logo == 0)
		return ;
	if (shell->logo == 1)
		logo1();
	else if (shell->logo == 2)
		logo2();
	else if (shell->logo == 3)
		logo3();
}

