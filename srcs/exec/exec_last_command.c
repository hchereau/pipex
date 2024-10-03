/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_last_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:36:26 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/03 15:20:50 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_last_command(char **cmd, char *outfile, int *pid)
{
	int	fd;

	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open");
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		execve(cmd[0], cmd,NULL);
		perror("execve");
		free_strs(cmd);
	}
}
