/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:13:36 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/09 13:52:06 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// static void	wait_process(pid_t pid, size_t i)
// {
// 	int	status;

// 	while (i > 0)
// 	{
// 		waitpid(pid, &status, 0);
// 		--i;
// 	}
// }

static void	process_child(t_cmd *cmd, char **env)
{
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fd_in, STDOUT_FILENO);
	cmd->cmd[0] = get_path_cmds(env, cmd->cmd[0]);
	execve(cmd->cmd[0], cmd, env);
	perror("execve");
	exit(EXIT_SUCCESS);
}

static void	parent_process(pid_t *pid, int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(*pid, NULL, 0);
}

static void	set_fd_cmd(int pipe_fd[2], t_cmd	*cmd)
{
	if (cmd->fd_in == WAIT_PIPEFD)
		cmd->fd_in = pipe_fd[0];
	if (cmd->fd_out == WAIT_PIPEFD)
		cmd->fd_out = pipe_fd[1];
}

t_state_function	exec_cmd(t_cmd *cmd, pid_t	*pid, char **env)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (ERROR);
	*pid = fork();
	if (*pid == -1)
		return (ERROR);
	if (*pid == 0)
	{
		set_fd_cmd(pipe_fd, cmd);
		process_child(cmd, env);
	}
	else
	{
		parent_process(pid, pipe_fd);
	}
	return (SUCCESS);
}

t_state_function	exec_cmds(t_cmd *cmds, char **env)
{
	int					i;
	pid_t				pid;
	t_state_function	ret;

	i = 0;
	while (cmds[i].cmd != NULL)
	{
		ret = exec_cmd(&cmds[i], &pid, env);
		if (ret != SUCCESS)
			return (ret);
		i++;
	}
	return (SUCCESS);
}
