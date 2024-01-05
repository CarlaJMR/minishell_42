/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 10:55:55 by mneves-l          #+#    #+#             */
/*   Updated: 2024/01/05 11:14:23 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    executor(t_data sh)
{
	sh.cmds->n_cmds = number_comands(sh.cmds);
	sh.cmds->fd_in = sh.cmds->redir[0];
	sh.cmds->fd_out = sh.cmds->redir[1];
	if(sh.flag_pipe == 0)
	{
		sh.flag_exec = 0;
		choose_builtin(&sh, sh.cmds, 0);
	}
	else
	{
		sh.flag_exec = 1;
		sh.store_std[0] = dup(STDIN_FILENO);
		sh.store_std[1] = dup(STDOUT_FILENO);
		dup2(sh.cmds->fd_in, STDIN_FILENO);
		pipe_process(sh.cmds, sh);
		dup2(sh.store_std[0], STDIN_FILENO);
		dup2(sh.store_std[1], STDOUT_FILENO);
		close(sh.store_std[0]);
		close(sh.store_std[1]);
	}
}

void    do_execve(t_data *data, t_cmd *cmd, int flag, int *pids)
{
	pid_t   child;
	char 	** our_env;

	our_env = env_to_matrix(data->env);
	
	if(flag)
	{
		execute_cmd(cmd->comand, our_env, pids);
		exit(EXIT_FAILURE);
	}
	else 
	{
		child = fork();
		if(child < 0)
			perror("error: fork");
		if(child == 0)
		{
			//signal(SIGQUIT, handle_quit);
			//signal(SIGINT, signal_handler);
			dup2(cmd->fd_in, STDIN_FILENO);
			dup2(cmd->fd_out, STDOUT_FILENO);
			execute_cmd(cmd->comand, our_env, NULL);
			exit(EXIT_FAILURE);
		}
		set_signals();
		signal(SIGINT, SIG_IGN);
		//signal(SIGQUIT, SIG_IGN);
		waitpid(child, NULL, 0);
		free_split(our_env);
	}
}

char    **env_to_matrix(t_env *env)
{
	char    **matriz;
	t_env   *tmp;
	int         i;
	char    *name;
	char    *content;

	tmp = env;
	matriz = (char **)malloc((ev_lstsize(env) + 1) * sizeof(char *));
	i = 0;

	while(tmp)
	{
		name = ft_strjoin(tmp->name, "=");
		content = ft_strjoin(name, tmp->content);
		free(name);
		matriz[i] = ft_strdup(content);
		free(content);
		i++;
		tmp = tmp->next;
	}
	matriz[i] = NULL;
	return(matriz);
}