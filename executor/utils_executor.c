/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:53:38 by mneves-l          #+#    #+#             */
/*   Updated: 2024/01/05 18:52:38 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    error(char *s)
{
    perror(s);
    exit(EXIT_FAILURE);
}

void    ft_wait(t_data sh)
{
    int     buffer;
    int i;
    //int exit_status;
    t_cmd   *tmp;

    i = -1;
    tmp = sh.cmds;
    while(tmp)
    {
        if (tmp->pid != -1)
            waitpid(tmp->pid, &buffer, 0);
        tmp = tmp->next;
    }
    /*if (WIFEXITED(buffer))
    {
        exit_status = WEXITSTATUS(buffer);
        set_exit_code(exit_status, 1);
    }-*/
    
    if (WIFSIGNALED(buffer))
        set_exit_code(128 + WTERMSIG(buffer), 1);
    else if (WIFEXITED(buffer))
	    set_exit_code(WEXITSTATUS(buffer), 1);
}