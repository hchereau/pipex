/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:06:58 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/03 11:40:09 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_pipex(t_input_data *data)
{
	int	pid;
	exec_commands(data->infile, data->cmds, &pid);
	exec_last_command(data, &pid);
	wait_process(pid);

}
