/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 10:55:55 by mneves-l          #+#    #+#             */
/*   Updated: 2024/01/05 19:12:30 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    executor(t_data sh)
{
	sh.cmds->n_cmds = number_comands(sh.cmds);
	sh.cmds->fd_in = sh.cmds->redir[0];
	sh.cmds->fd_out = sh.cmds->redir[1];
	if(sh.flag_pipe == 0 && is_builtin(sh.cmds))
		choose_builtin(&sh, sh.cmds, 0, 1);
	else
	{
		create_pipe(sh, sh.cmds, -1);
	}
}

void    create_pipe(t_data sh, t_cmd *cmd, int i)
{
    t_cmd   *tmp;
    tmp = cmd;
    
    while(++i < cmd->n_cmds && tmp)
    {
        tmp->pid = -1;
        if(pipe(tmp->pip_fd) == 1)
            error("error:");
        tmp->pid = process_child(sh, tmp);
        tmp = tmp->next;
    }
	// pids[i] = fork();
    // if(pids[i] < 0)
    //     error("error: fork");
    //if(!pids[i])
        //last_process(tmp, sh);
    // else
    // {
    // }
    ft_wait(sh);
}

// void    last_process(t_cmd *cmd, t_data data)
// {
//     cmd->fd_in = cmd->redir[0];
//     cmd->fd_out = cmd->redir[1];
//     if(cmd->fd_out > 2)
//         dup2(cmd->fd_out, STDOUT_FILENO);
//     if(cmd->fd_in > 2)
//         dup2(cmd->fd_in, STDIN_FILENO);
//     //close(data.store_std[0]);
//     //close(data.store_std[1]);
//     choose_builtin(&data, cmd, 1);

// }

pid_t    process_child(t_data sh, t_cmd *cmd)
{
    pid_t   pid;
    
    if (cmd->next)
        cmd->fd_out = cmd->pip_fd[1];
    if (cmd->prev)
        cmd->fd_in = cmd->prev->pip_fd[0];
    if (cmd->redir[0] > 2)
        cmd->fd_in = cmd->redir[0];
    if (cmd->redir[1] > 2)
        cmd->fd_out = cmd->redir[1];
    pid = fork();
    if(pid < 0)
        error("Error: ");
    if(pid == 0)
        child(sh, cmd);
    else
    {
        if (cmd->redir[0] > 2)
            close(cmd->redir[0]);
        if (cmd->redir[1] > 2)
            close(cmd->redir[1]);
        close(cmd->pip_fd[1]);
        if (!cmd->next)
            close(cmd->pip_fd[0]);
        if (cmd->prev)
            close(cmd->prev->pip_fd[0]);
    }
    return (pid);
}

void    child(t_data sh, t_cmd *cmd)
{
    if(cmd->fd_in != 0)
        dup2(cmd->fd_in, STDIN_FILENO);
    if (cmd->fd_out != 1)
        dup2(cmd->fd_out, STDOUT_FILENO);
    close(cmd->pip_fd[0]);
    close(cmd->pip_fd[1]);
    if (cmd->prev)
        close(cmd->prev->pip_fd[0]);
    if (cmd->redir[0] > 2)
        close(cmd->redir[0]);
    if (cmd->redir[1] > 2)
        close(cmd->redir[1]);
    choose_builtin(&sh, cmd, 1, 0);
}

