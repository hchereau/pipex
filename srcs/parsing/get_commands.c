/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:59:41 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/02 15:41:44 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	**get_path(char *env)
{
	int		i;
	char	**path;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], ENV_PATH, SIZE_ENV_PATH) == 0)
		{
			path = ft_split(env[i] + SIZE_ENV_PATH, ':');
			if (path == NULL)
			{
				ft_putendl_fd("Error: malloc failed in get_path", STDERR_FILENO);
				return (NULL);
			}
			return (path);
		}
		++i;
	}
	ft_putendl_fd("Error: PATH not found in env", STDERR_FILENO);
	return (NULL);
}

static char	*get_path_from_env(char **paths, char *str)
{
	size_t	i;

	i = 0;
	while (paths[i] != NULL)
	{
		if (access(paths[i], F_OK) == 0 || access(paths[i], X_OK) == 0)
			return (ft_strjoin(paths[i], str));
		++i;
	}
	return (str);
}

static char	*get_relative_path(char *str, char **env)
{
	char	**paths;
	char	*cmd;
	size_t	i;

	paths = get_path(env);
	if (paths == NULL)
		return (NULL);
	if (access(str, F_OK) == 0 || access(str, X_OK) == 0)
		cmd = ft_strdup(str);
	else
	{
		cmd = get_path_from_env(paths, str);
	}
	free_strs(paths);
	return (cmd);
}

static char	**get_commands(char **strs, char **env)
{
	char	**cmds;
	int		i;

	i = 0;
	cmds = malloc(sizeof(char *) * (ft_strslen(strs)));
	if (cmds == NULL)
	{
		ft_putendl_fd("Error: malloc failed in get_commands", STDERR_FILENO);
		return (NULL);
	}
	while (strs[i + 1] != NULL)
	{
		cmds[i] = get_relative_path(strs[i], env);
		if (cmds[i] == NULL)
		{
			ft_putendl_fd("Error: malloc failed in get_commands",
				STDERR_FILENO);
			free_strs(cmds);
			return (NULL);
		}
		++i;
	}
	cmds[i] = NULL;
	return (cmds);
}
