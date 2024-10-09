/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds_with_files.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:03:08 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/09 10:36:01 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_state_function	exec_cmds_with_files(t_data	*data, char **env)
{

	manages_fd_cmds(data->cmds);



	return (SUCCESS);
}
