/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds_with_files.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:03:08 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/09 11:31:02 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_state_function	close_fd_in_and_out(t_cmd *cmds)
{
	int	i;

	i = 0;
	close(cmds[i].fd_in);
	while (cmds[i + 1].cmd != NULL)
	{
		i++;
	}
	close(cmds[i].fd_out);
	return (SUCCESS);
}

t_state_function	exec_cmds_with_files(t_data	*data, char **env)
{
	manages_fd_cmds(data->cmds);
	close_fd_in_and_out(data->cmds);
	return (SUCCESS);
}
