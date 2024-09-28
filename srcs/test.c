/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:05:14 by hucherea          #+#    #+#             */
/*   Updated: 2024/09/28 17:13:50 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	main(int ac, char **av)
// {
// 	int	pipefd[2];
// 	int	pid;
// 	int status;
// 	char *cmd1[] = {"/bin/ls", "-l", NULL};
// 	char *cmd2[] = {"/bin/wc", "-l", NULL};

// 	(void)ac;
// 	(void)av;
// 	pipe(pipefd);
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		return (1);
// 	}
// 	if (pid == 0) // Child
// 	{
// 		close(pipefd[0]);
// 		dup2(pipefd[1], STDOUT_FILENO);
// 		execve("/bin/ls", cmd1, NULL);
// 	}
// 	else // Parent
// 	{
// 		close(pipefd[1]);
// 		dup2(pipefd[0], STDIN_FILENO);
// 		execve("/bin/wc", cmd2, NULL);
// 		waitpid(-1, &status, 0);
// 		close(pipefd[0]);
// 	}
// }

int	main(int ac, char **av)
{
	int	pipefd[2];
	int	pid;
	int i = 0;
	int status;
	char *cmd1[] = {"/bin/ls", "-l", NULL};
	char *cmd2[] = {"/bin/grep", "d", NULL};
	char *cmd3[] = {"/bin/wc", "-l", NULL};

	(void)ac;
	(void)av;
	while (i < 2)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (1);
		}
		if (pid == 0)
		{
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			if (i == 0)
				execve(cmd1[0], cmd1, NULL);
			else if (i == 1)
				execve(cmd2[0], cmd2, NULL);
			perror("execve");
			return (EXIT_FAILURE);
		}
		else
		{
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
		}
		i++;
	}
	pid = fork();
	if (pid== 0)
	{
		execve(cmd3[0], cmd3, NULL);
		perror("execve");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < 3)
	{
		waitpid(pid, &status, 0);
		i++;
	}
}
