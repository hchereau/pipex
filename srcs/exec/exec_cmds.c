/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:13:36 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/09 17:58:42 by hucherea         ###   ########.fr       */
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
	printf("in process_child : cmd->fd_in = %d\n", cmd->fd_in);
	printf("in process_child : cmd->fd_out = %d\n", cmd->fd_out);
	printf("------------------------\n");
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
	close(cmd->fd_in);
	close(cmd->fd_out);
	cmd->tokens[0] = get_path_cmds(env, cmd->tokens[0]);
	if (cmd->tokens[0] == NULL)
	{
		perror("get_path_cmds");
		exit(EXIT_FAILURE);
	}
	execve(cmd->tokens[0], cmd->tokens, env);
	perror("execve");
	exit(EXIT_FAILURE);
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
	else
		dup2(pipe_fd[1], cmd->fd_out);
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
		printf("cmd->fd_in = %d\n", cmd->fd_in);
		printf("pipe_fd[1] = %d\n", pipe_fd[0]);
		printf("cmd->fd_out = %d\n", cmd->fd_out);
		printf("pipe_fd[0] = %d\n", pipe_fd[1]);
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

	i = 0;
	while (cmds[i].tokens != NULL)
	{
		exec_cmd(&cmds[i], &pid, env);
		++i;
	}
	return (SUCCESS);
}
