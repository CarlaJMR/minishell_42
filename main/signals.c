/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2024/01/12 11:23:42 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		set_exit_code(130, 1);
	}
}

void	signals_here_doc(int sign)
{
	(void)sign;
	write(1, "^C\n", 3);
	exit(set_exit_code(130, 1));
}

void	set_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	child_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (signal == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", 1);
	return ;
}

void	child_signal(void)
{
	signal(SIGINT, child_signal_handler);
	signal(SIGQUIT, child_signal_handler);
	return ;
}
