/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:46:26 by mneves-l          #+#    #+#             */
/*   Updated: 2024/01/02 14:48:48 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    pipe_process(t_cmd *cmd, t_data data)
{
    t_cmd   *tmp;
    int     *pids;
    int     i;
    int     j;
    j = 0;
    i = 0;

    tmp = cmd;
    pids = ft_calloc(cmd->n_cmds, sizeof(int));
    while(tmp && i++ < cmd->n_cmds - 1)
    {
        pids[j++] = child_process(data, tmp, pids);
        tmp = tmp->next;
    }
    i = fork();
    if(i < 0)
        error("error: fork");
    if(!i)
        last_process(tmp, data, pids);
    else
    {
        close(STDIN_FILENO);
		close(STDOUT_FILENO);
        wait_all(tmp, pids);
        waitpid(i, NULL, 0);
    }
    free(pids);
}

void    wait_all(t_cmd *cmd, int *pids)
{
    int j;
    j = 0;
    while (cmd->prev)
        cmd = cmd->prev;
    while(j< cmd->n_cmds)
    {
        if(pids[j])
            waitpid(pids[j], NULL, 0);
        j++;
    }
}

void    last_process(t_cmd *cmd, t_data data, int *pids)
{
    if(cmd->fd_out > 2)
        dup2(cmd->fd_out, STDOUT_FILENO);
    close(data.store_std[0]);
    close(data.store_std[1]);
    choose_builtin(&data, cmd, pids);

}

int     child_process(t_data data, t_cmd *cmd, int *pids)
{
    pid_t   child;
    int     pipefd[2];

    if(pipe(pipefd) < 0)
        error("error: pipe");
    child = fork();
    if(child < 0)
        error("error: fork");
    if(child == 0)
        do_child(data, cmd, pids, pipefd);
    else 
    {
        if(cmd->fd_in > 2)
            dup2(cmd->fd_in, STDIN_FILENO);
        else
            dup2(pipefd[0], STDIN_FILENO);
        (close(pipefd[0]), close(pipefd[1]));
    }
    return(child); 
}

void    do_child(t_data data, t_cmd *cmd, int *pids, int *pipefd)
{
    if(cmd->fd_out > 2)
        dup2(cmd->fd_out, STDOUT_FILENO);
    else 
        dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[0]);
    close(pipefd[1]);
    close(data.store_std[0]);
    close(data.store_std[1]);
    choose_builtin(&data, cmd, pids);

}

void    error(char *s)
{
    perror(s);
    exit(EXIT_FAILURE);
}