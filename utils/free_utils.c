/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:55:55 by mneves-l          #+#    #+#             */
/*   Updated: 2023/12/29 11:27:16 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_comand(t_cmd **lst)
{
	t_cmd	*aux;

	while (lst && *lst)
	{
		aux = (*lst)->next;
		//close((*lst)->redir[0]);
		//close((*lst)->redir[1]);
		free_split((*lst)->comand);
		free (*lst);
		*lst = aux;
	}
}

void	free_split(char **str)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (str[size])
		size++;
	while (i < size)
		free(str[i++]);
	free(str);
}

void	free_env(t_env **ev)
{
	t_env	*aux;

	while (ev && *ev)
	{
		aux = (*ev)->next;
		free((*ev)->name);
		free((*ev)->content);
		free (*ev);
		*ev = aux;
	}
}
