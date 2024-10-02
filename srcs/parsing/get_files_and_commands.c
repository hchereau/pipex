/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files_and_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:04:57 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/02 15:01:17 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_state_fonction	get_files(char **infile, char **outfile, char **strs)
{
	*infile = ft_strdup(strs[0]);
	if (*infile == NULL)
	{
		ft_putendl_fd("Error: malloc failed in get_files", STDERR_FILENO);
		return (FAILURE);
	}
	*outfile = ft_strdup(strs[ft_strslen(strs) - 1]);
	if (*outfile == NULL)
	{
		ft_putendl_fd("Error: malloc failed in get_files", STDERR_FILENO);
		free(*infile);
		*infile = NULL;
		return (FAILURE);
	}
	return (SUCCESS);
}

t_input_data	*get_files_and_commands(char **strs, char **env)
{
	t_input_data	*data;

	data = (t_input_data *)malloc(sizeof(t_input_data));
	if (data == NULL)
	{
		ft_putendl_fd("Error: malloc failed in get_files_and_commands",
			STDERR_FILENO);
		return (NULL);
	}
	if (get_files(&data->infile, &data->outfile, strs) == SUCCESS)
	{
		data->cmd = get_commands(strs + 1, env);
	}
	if (data->cmd == NULL)
	{
		free_data(data);
		return (NULL);
	}
	return (data);
}
