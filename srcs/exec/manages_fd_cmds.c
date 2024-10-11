/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manages_fd_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:00:07 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/11 16:07:12 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// static t_state_function	manage_fd_infile(const char *path_infile,
// 		int *fd_in_cmd)
// {
// 	int	fd_in;

// 	if (path_infile != NULL)
// 	{
// 		// fd_in = open(path_infile, O_RDONLY);
// 		// if (fd_in == -1)
// 		// 	return (ERROR);
// 		// *fd_in_cmd = fd_in;
// 		// dup2(fd_in, STDIN_FILENO);
// 		// close(fd_in);
// 		fd_in = 0;
// 	}
// 	else
// 	{
// 		fd_in_cmd = NULL;
// 		return (FAILURE);
// 	}
// 	return (SUCCESS);
// }

// static t_state_function	manage_fd_outfile(const char *path_outfile,
// 			int *fd_out_cmd)
// {
// 	int	fd_out;

// 	if (path_outfile != NULL)
// 	{
// 		// fd_out = open(path_outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		// if (fd_out == -1)
// 		// 	return (ERROR);
// 		// *fd_out_cmd = fd_out;
// 		// // close(fd_out);
// 		fd_out = 0;
// 	}
// 	else
// 	{
// 		fd_out_cmd = NULL;
// 		return (FAILURE);
// 	}
// 	return (SUCCESS);
// }

// t_state_function	manage_pipe_fd(t_cmd *cmds, size_t *i)
// {
// 	*i = 1;
// 	cmds[0].fd_in = WAIT_PIPEFD;
// 	cmds[0].fd_out = WAIT_PIPEFD;
// 	while (cmds[*i + 1].tokens != NULL)
// 	{
// 		cmds[*i].fd_in = WAIT_PIPEFD;
// 		cmds[*i].fd_out = WAIT_PIPEFD;
// 		++(*i);
// 	}
// 	cmds[*i].fd_in = WAIT_PIPEFD;
// 	cmds[*i].fd_out = WAIT_PIPEFD;
// 	return (SUCCESS);
// }

// t_state_function	manages_fd_cmds(t_cmd *cmds,
// 	const char *path_infile, const char *path_outfile)
// {
// 	size_t				i;
// 	t_state_function	state;

// 	state = SUCCESS;
// 	state = manage_fd_infile(path_infile, &cmds[0].fd_in);
// 	if (state == SUCCESS)
// 	{
// 		state = manage_pipe_fd(cmds, &i);
// 		if (state == SUCCESS)
// 			state = manage_fd_outfile(path_outfile, &cmds[i].fd_out);
// 	}
// 	return (state);
// }


static void	manages_fd_infile(const char *infile, int *fd_in, int *fd_out)
{
	if (infile != NULL)
	{
		*fd_out = WAIT_PIPEFD;
		*fd_in = open(infile, O_RDONLY);
		if (*fd_in == -1)
		{
			ft_putendl_fd("Error: open failed", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
}

static void	manages_fd_outfile(const char *outfile, int *fd_out, int *fd_in)
{
	if (outfile != NULL)
	{
		*fd_in = WAIT_PIPEFD;
		*fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fd_out == -1)
		{
			ft_putendl_fd("Error: open failed", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		dup2(*fd_out, STDOUT_FILENO);
		close(*fd_out);
	}
}

void	manage_pipe_fds(t_cmd *cmds, size_t i)
{
	cmds[i].fd_in = WAIT_PIPEFD;
	cmds[i].fd_out = WAIT_PIPEFD;
}

// static void	printf_strs(char **strs)
// {
// 	size_t	i;

// 	i = 0;
// 	while (strs[i] != NULL)
// 	{
// 		printf("strs[%zu]: %s\n", i, strs[i]);
// 		++i;
// 	}
// }

void	manages_fd_cmds(t_cmd	*cmds, const char *infile, const char *outfile,
	size_t i)
{
	if (i == INDEX_FIRST_CMD)
	{
		manages_fd_infile(infile, &cmds[i].fd_in, &cmds[i].fd_out);
	}
	else if (cmds[i + 1].tokens == NULL)
	{
		manages_fd_outfile(outfile, &cmds[i].fd_out, &cmds[i].fd_in);
	}
	else
	{
		manage_pipe_fds(cmds, i);
	}
}
