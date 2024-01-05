/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2024/01/05 11:18:29 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
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

void	handle_quit(int sign)
{
	//pid_t	pid;
	//int		status;

	(void)sign;
	/*pid = waitpid(-1, &status, 0);
	if (pid == -1)
		SIG_IGN ;
	else*/
	{
		ft_putendl_fd("Quit (core dumped)\n", 1);
		signal(SIGQUIT, SIG_DFL);
		exit(set_exit_code(131, 1));
	}
}

int	set_exit_code(int i, int flag)
{
	static int	code;

	if (flag)
		code = i;
	return (code);
}
