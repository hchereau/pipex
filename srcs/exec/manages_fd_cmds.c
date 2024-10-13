/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manages_fd_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:00:07 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/13 18:31:08 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_state_function	manages_fd_infile(const char *infile, int *fd_in,
	int *fd_out)
{
	if (infile != NULL)
	{
		*fd_out = WAIT_PIPEFD;
		*fd_in = open(infile, O_RDONLY);
		if (*fd_in == -1)
		{
			ft_putendl_fd("Error: open failed", STDERR_FILENO);
			return (FAILURE);
		}
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
		return (SUCCESS);
	}
	return (FAILURE);
}

static t_state_function	manages_fd_outfile(const char *outfile,
	const char *infile, int *fd_out, int *fd_in)
{
	if (outfile != NULL)
	{
		*fd_in = WAIT_PIPEFD;
		if (ft_strncmp(infile, FILE_TEMP_HERE_DOC, LEN_HERE_DOC) == 0)
		{
			*fd_out = open(outfile, O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		}
		else
			*fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fd_out == -1)
		{
			ft_putendl_fd("Error: open failed", STDERR_FILENO);
			return (FAILURE);
		}
		dup2(*fd_out, STDOUT_FILENO);
		close(*fd_out);
		return (SUCCESS);
	}
	return (FAILURE);
}

void	manage_pipe_fds(t_cmd *cmds, size_t i)
{
	cmds[i].fd_in = WAIT_PIPEFD;
	cmds[i].fd_out = WAIT_PIPEFD;
}

t_state_function	manages_fd_cmds(t_cmd	*cmds, const char *infile,
	const char *outfile, size_t i)
{
	int			fd;

	if (i == INDEX_FIRST_CMD)
	{
		if (manages_fd_infile(infile, &cmds[i].fd_in, &cmds[i].fd_out)
			== FAILURE)
		{
			fd = open("/dev/null", O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
			return (FAILURE);
		}
	}
	else if (cmds[i + 1].tokens == NULL)
	{
		return (manages_fd_outfile(outfile, infile, &cmds[i].fd_out,
				&cmds[i].fd_in));
	}
	else
	{
		manage_pipe_fds(cmds, i);
	}
	return (SUCCESS);
}
