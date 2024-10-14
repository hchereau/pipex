/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:13:36 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/14 11:22:48 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	wait_child(pid_t *pid, size_t i)
{
	size_t	i_cmd;

	i_cmd = 0;
	while (i_cmd < i)
	{
		waitpid(pid[i_cmd], NULL, 0);
		++i_cmd;
	}
}

static void	child_process(t_cmd *cmd, int *pipefd, char **env)
{
	if (cmd->fd_out == WAIT_PIPEFD)
	{
		dup2(pipefd[1], STDOUT_FILENO);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	if (cmd->tokens[0] == NULL)
	{
		ft_putendl_fd("Error: command is NULL", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	cmd->tokens[0] = get_path_cmds(env, cmd->tokens[0]);
	execve(cmd->tokens[0], cmd->tokens, env);
	perror("Error: execve failed");
	free_strs(cmd->tokens);
	exit(EXIT_FAILURE);
}

static void	parent_process(int *pipefd)
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
}

static void	exec_cmd(t_cmd *cmd, char **env, pid_t *pid)
{
	int	pipefd[PIPEFD_SIZE];

	if (pipe(pipefd) == -1)
	{
		ft_putendl_fd("Error: pipe failed", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	*pid = fork();
	if (*pid == -1)
	{
		ft_putendl_fd("Error: fork failed", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (*pid == 0)
	{
		child_process(cmd, pipefd, env);
	}
	else
		parent_process(pipefd);
}

t_state_function	exec_cmds(t_cmd *cmds, char **env, const char *infile,
		const char *outfile)
{
	size_t	i;
	pid_t	*pid;

	i = 0;
	pid = (pid_t *)malloc(sizeof(pid_t) * (ft_strlen_cmd(cmds) + 1));
	if (pid == NULL)
		return (FAILURE);
	while (cmds[i].tokens != NULL)
	{
		if (manages_fd_cmds(cmds, infile, outfile, i) != FAILURE)
			exec_cmd(&cmds[i], env, &pid[i]);
		++i;
	}
	wait_child(pid, i);
	free(pid);
	return (SUCCESS);
}
