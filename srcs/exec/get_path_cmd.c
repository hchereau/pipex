/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:46:22 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/14 11:41:43 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	**get_paths_from_env(char **env)
{
	char	**paths;

	paths = NULL;
	while (*env != NULL)
	{
		if (ft_strncmp(*env, ENV_PATH, SIZE_ENV_PATH) == 0)
		{
			paths = ft_split(*env + SIZE_ENV_PATH, ':');
			if (paths == NULL)
				return (NULL);
			return (paths);
		}
		++env;
	}
	ft_putendl_fd("Error: PATH not found in env", STDERR_FILENO);
	return (paths);
}

static bool	verif_cmd(char *cmd)
{
	return (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0);
}

char	*get_path_cmds(char **env, char *cmd)
{
	char	**paths;
	char	*temp_path;
	char	*temp_cmd;
	size_t	i;

	i = 0;
	if (verif_cmd(cmd) == true)
		return (cmd);
	paths = get_paths_from_env(env);
	temp_cmd = ft_strdup(cmd);
	while (verif_cmd(temp_cmd) == false && paths != NULL && paths[i] != NULL)
	{
		free(temp_cmd);
		temp_path = ft_strjoin(paths[i], "/");
		if (temp_path == NULL)
			break ;
		temp_cmd = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (temp_cmd == NULL)
			break ;
		++i;
	}
	free(cmd);
	free_strs(paths);
	return (temp_cmd);
}
