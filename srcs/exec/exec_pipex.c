/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:06:58 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/03 15:14:57 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static size_t	ft_strsslen(char ***strs)
{
	size_t	len;

	len = 0;
	while (strs[len] != NULL)
		++len;
	return (len);
}

static void	wait_process(int *pid, int cmds_len)
{
	while (cmds_len > 0)
	{
		waitpid(*pid, NULL, 0);
		--cmds_len;
	}
}

void	exec_pipex(t_input_data *data)
{
	int	pid;
	exec_commands(data->infile, data->cmds, &pid);
	exec_last_command(data->cmds[ft_strsslen(data->cmds) - 1], data->outfile, &pid);
	wait_process(&pid, ft_strsslen(data->cmds));

}
