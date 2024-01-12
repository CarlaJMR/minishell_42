/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:08:28 by mneves-l          #+#    #+#             */
/*   Updated: 2024/01/12 13:03:45 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_name(char *cmd)
{
	int		i;
	char	*n;
	int		size;

	if (ft_strchr(cmd, '=') == NULL)
		size = ft_strlen(cmd);
	else
		size = g_size(cmd, '=');
	n = ft_substr(cmd, 0, size);
	i = 0;
	while (n && n[i])
	{
		if (((n[i] > 32 && n[i] < 48) || (n[i] > 57 && n[i] < 65) \
			|| (n[i] > 90 && n[i] < 97) || (n[i] > 122 && n[i] < 127)) \
			&& (n[i] != '_'))
		{
			error_export(n);
			free(n);
			return (1);
		}
		i++;
	}
	free(n);
	return (0);
}

void	error_export(char *name)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	set_exit_code(1, 1);
}
