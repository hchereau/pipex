/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:40:11 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/03 13:23:24 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	child_process(char *infile, char **cmd, int *pipefd[2])
{

}

static void	process(char *infile, char **cmd, int *pipefd[2], int *pid)
{
	pipe(*pipefd);
	*pid = fork();
	if (*pid == 0)
	{
		child_process(infile, cmd, pipefd);
	}
	else
	{
		dup2(*pipefd[0], STDIN_FILENO);
		close(*pipefd[1]);
		close(*pipefd[0]);
	}
}

t_state_function	exec_commands(char *infile, char ***cmds, int *pid)
{
	size_t	i;
	int		pipefd[2];

	i = 0;
	dup2(infile, STDIN_FILENO);
	while (cmds[i + 1] != NULL)
	{
		process(infile, cmds[i], &pipefd, pid);
		++i;
	}
}
