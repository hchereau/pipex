/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manages_fd_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:00:07 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/09 18:01:45 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_state_function	manage_fd_infile(const char *path_infile,
		int *fd_in_cmd)
{
	int	fd_in;

	if (path_infile != NULL)
	{
		fd_in = open(path_infile, O_RDONLY);
		printf("path_infile: %s\n", path_infile);
		printf("fd_in: %d\n", fd_in);
		if (fd_in == -1)
			return (ERROR);
		*fd_in_cmd = fd_in;
	}
	else
	{
		fd_in_cmd = NULL;
		return (FAILURE);
	}
	return (SUCCESS);
}

static t_state_function	manage_fd_outfile(const char *path_outfile,
			int *fd_out_cmd)
{
	int	fd_out;

	if (path_outfile != NULL)
	{
		fd_out = open(path_outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		printf("path_outfile: %s\n", path_outfile);
		printf("fd_out: %d\n", fd_out);
		if (fd_out == -1)
			return (ERROR);
		*fd_out_cmd = fd_out;
	}
	else
	{
		fd_out_cmd = NULL;
		return (FAILURE);
	}
	return (SUCCESS);
}

t_state_function	manage_pipe_fd(t_cmd *cmds, size_t *i)
{
	*i = 1;
	cmds[0].fd_out = WAIT_PIPEFD;
	while (cmds[*i + 1].tokens != NULL)
	{
		cmds[*i].fd_in = WAIT_PIPEFD;
		cmds[*i].fd_out = WAIT_PIPEFD;
		++(*i);
	}
	cmds[*i].fd_in = WAIT_PIPEFD;
	return (SUCCESS);
}

t_state_function	manages_fd_cmds(t_cmd *cmds,
	const char *path_infile, const char *path_outfile)
{
	size_t				i;
	t_state_function	state;

	state = manage_fd_infile(path_infile, &cmds[0].fd_in);
	if (state == SUCCESS)
	{
		state = manage_pipe_fd(cmds, &i);
		if (state == SUCCESS)
			state = manage_fd_outfile(path_outfile, &cmds[i].fd_out);
	}
	return (state);
}
