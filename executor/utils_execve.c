/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:03:47 by mneves-l          #+#    #+#             */
/*   Updated: 2024/01/08 16:11:25 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*to_path(char *cmd, char **envp)
{
	int		i;
	char	*paths;
	char	**path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	paths = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	path = ft_split(paths, ':');
	free(paths);
	if (!path || !*path)
		return (NULL);
	return (path_to_cmd(cmd, path));
}

char	*path_to_cmd(char *cmd, char **path)
{
	int		i;
	char	*tmp;
	char	*final;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		final = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(final, F_OK & X_OK) != -1)
		{
			free_split(path);
			return (final);
		}
		free(final);
		i++;
	}
	free_split(path);
	return (cmd);
}

void	execute_cmd(char **cmd, char **envp)
{
	char	*path;
	int 	flag;
	int 	i;

	i = 0;
	flag = 0;
	while(envp[i])
	{
		if(!ft_strncmp(envp[i], "PATH=", 5))
			flag = 1;
		i++;
	}
	if(flag == 1)
		path = to_path(cmd[0], envp);
	if (execve(path, cmd, NULL) == -1 || flag == 0)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(" :command not found", 2);
		set_exit_code(127, 1);
		free(path);
		return ;
	}
	free(path);
}

void    do_execve(t_data *data, t_cmd *cmd, int flag)
{
	(void)flag;
	// pid_t   child;
	char 	** our_env;

	our_env = env_to_matrix(data->env);
	
	execute_cmd(cmd->comand, our_env);
	// if(flag)
	// {
	// 	execute_cmd(cmd->comand, our_env);
	// 	exit(EXIT_FAILURE);
	// }
	// else 
	// {
	// 	child = fork();
	// 	if(child < 0)
	// 		perror("error: fork");
	// 	if(child == 0)
	// 	{
	// 		dup2(cmd->fd_in, STDIN_FILENO);
	// 		dup2(cmd->fd_out, STDOUT_FILENO);
	// 		execute_cmd(cmd->comand, our_env);
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	waitpid(child, NULL, 0);
	// 	free_split(our_env);
	// }
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
