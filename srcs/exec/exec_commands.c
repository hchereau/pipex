/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:40:11 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/04 15:23:37 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	child_process(char **cmd, int (*pipefd)[2])
{
	dup2((*pipefd)[1], STDOUT_FILENO);
	close((*pipefd)[0]);
	close((*pipefd)[1]);
	if (cmd[0] != NULL)
		execve(cmd[0], cmd, NULL);
	perror("execve");
	// free_strs(cmd);
	return ;
	// exit(EXIT_FAILURE);
}

static void	process(char **cmd, int (*pipefd)[2], int *pid)
{
	pipe(*pipefd);
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		free_strs(cmd);
		exit(EXIT_FAILURE);
	}
	else if (*pid == 0)
	{
		child_process(cmd, pipefd);
	}
	else
	{
		dup2((*pipefd)[0], STDIN_FILENO);
		close((*pipefd)[1]);
		close((*pipefd)[0]);
	}
}

void	exec_commands(char *infile, char ***cmds, int *pid)
{
	size_t	i;
	int		pipefd[2];
	int		fd;

	i = 0;
	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	while (cmds[i + 1] != NULL)
	{
		process(cmds[i], &pipefd, pid);
		++i;
	}
}
