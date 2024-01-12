/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:53:38 by mneves-l          #+#    #+#             */
/*   Updated: 2024/01/12 15:33:11 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	do_execve(t_data *data, t_cmd *cmd)
{
	char	**our_env;

	if (cmd->redir[0] != -1)
	{
		our_env = env_to_matrix(data->env);
		execute_cmd(cmd->comand, our_env, data);
	}
	exit(1);
}

void	ft_wait(t_data sh)
{
	int		buffer;
	t_cmd	*tmp;

	buffer = 0;
	tmp = sh.cmds;
	while (tmp)
	{
		if (tmp->pid != -1)
			waitpid(tmp->pid, &buffer, 0);
		tmp = tmp->next;
	}
	if (WIFSIGNALED(buffer))
		set_exit_code(128 + WTERMSIG(buffer), 1);
	else if (WIFEXITED(buffer))
		set_exit_code(WEXITSTATUS(buffer), 1);
}
