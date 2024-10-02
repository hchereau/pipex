/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:59:41 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/02 17:55:08 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	**get_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], ENV_PATH, SIZE_ENV_PATH) == 0)
		{
			paths = ft_split(env[i] + SIZE_ENV_PATH, ':');
			if (paths == NULL)
			{
				ft_putendl_fd("Error: malloc failed in get_path",
					STDERR_FILENO);
				return (NULL);
			}
			return (paths);
		}
		++i;
	}
	ft_putendl_fd("Error: PATH not found in env", STDERR_FILENO);
	return (NULL);
}

static char	*make_relative_path(char *cmd, char *path)
{
	char		*relative_path;
	char		*cmd_with_path;

	relative_path = ft_strjoin(path, "/");
	if (relative_path == NULL)
		return (NULL);
	cmd_with_path = ft_strjoin(relative_path, cmd);
	if (cmd_with_path == NULL)
	{
		free(relative_path);
		return (NULL);
	}
	free(relative_path);
	return (cmd_with_path);
}

static char	*get_path_from_env(char **paths, char *str)
{
	char	*cmd;
	size_t	i;

	i = 0;
	while (paths[i] != NULL)
	{
		cmd = make_relative_path(str, paths[i]);
		if (cmd == NULL)
		{
			return (NULL);
		}
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
			return (cmd);
		free(cmd);
		++i;
	}
	return (str);
}

static char	*get_relative_path(char *str, char **env)
{
	char	**paths;
	char	*cmd;

	paths = get_paths(env);
	if (paths == NULL)
		return (NULL);
	if (access(str, F_OK) == 0 && access(str, X_OK) == 0)
		cmd = ft_strdup(str);
	else
	{
		cmd = get_path_from_env(paths, str);
		if (cmd == NULL)
		{
			ft_putendl_fd("Error: malloc failed in get_relative_path",
				STDERR_FILENO);
			free_strs(paths);
			return (NULL);
		}
	}
	free_strs(paths);
	return (cmd);
}

char	**get_commands(char **strs, char **env)
{
	char	**cmds;
	size_t	i;

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
