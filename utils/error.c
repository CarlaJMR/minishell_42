/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:27:36 by mneves-l          #+#    #+#             */
/*   Updated: 2024/01/12 13:10:31 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	message_heredoc(char *limiter)
{
	ft_putstr_fd("warning: here-doc delimited by ", 2);
	ft_putstr_fd("end-of-file (wanted '", 2);
	ft_putstr_fd(limiter, 2);
	ft_putendl_fd("')", 2);
}
