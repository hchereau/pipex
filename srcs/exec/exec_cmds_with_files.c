/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds_with_files.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:03:08 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/09 17:59:58 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_state_function	close_fd_in_and_out(t_cmd *cmds)
{
	int	i;

	i = 0;
	close(cmds[i].fd_in);
	while (cmds[i + 1].tokens != NULL)
	{
		i++;
	}
	close(cmds[i].fd_out);
	return (SUCCESS);
}

t_state_function	exec_cmds_with_files(t_input_data	*data, char **env)
{
	if (manages_fd_cmds(data->cmds, data->infile, data->outfile) == FAILURE)
	{
		free_data(data);
		return (FAILURE);
	}
	close_fd_in_and_out(data->cmds);
	exec_cmds(data->cmds, env);
	free_data(data);
	return (SUCCESS);
}

