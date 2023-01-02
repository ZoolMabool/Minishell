/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:29:42 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:29:44 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

char	**copy_envp(char **envp)
{
	char	**envp_l;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	envp_l = malloc(sizeof(char *) * (i + 1));
	envp_l[i] = NULL;
	i = 0;
	while (envp[i])
	{
		envp_l[i] = ft_strdup(envp[i]);
		i++;
	}
	return (envp_l);
}

char	*check_line_path(char **envp_l)
{
	int		i;

	i = 0;
	while (envp_l[i])
	{
		if ((ft_strncmp(envp_l[i], "PATH=", 5)) == 0)
		{
			return (envp_l[i] + 5);
		}
		i++;
	}
	return (0);
}

char	**get_path(char *envp_path)
{
	char	*tmp;
	char	**paths;
	int		i;

	i = 0;
	paths = ft_split(envp_path, ':');
	while (paths[i])
	{
		tmp = ft_strdup(paths[i]);
		free(paths[i]);
		paths[i] = ft_strjoin(tmp, "/");
		free(tmp);
		tmp = NULL;
		i++;
	}
	return (paths);
}

char	**get_cmd(char *cmd, char **paths)
{
	int		i;
	char	**cmd_split;
	char	*cmd_path;

	i = 0;
	cmd_split = ft_split(cmd, ' ');
	if (access(cmd_split[0], F_OK | X_OK) == 0)
		return (cmd_split);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd_split[0]);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free(cmd_split[0]);
			cmd_split[0] = cmd_path;
			return (cmd_split);
		}
		free(cmd_path);
		i++;
	}
	free_2d_arr(cmd_split);
	return (NULL);
}
