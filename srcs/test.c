/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:05:14 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/04 11:14:13 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0;37m"

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

// int	main(int ac, char **av)
// {
// 	int	pipefd[2];
// 	int	pid;
// 	int i = 0;
// 	int status;
// 	char *cmd1[] = {"/bin/ls", "-l", NULL};
// 	char *cmd2[] = {"/bin/grep", "d", NULL};
// 	char *cmd3[] = {"/bin/wc", "-l", NULL};

// 	(void)ac;
// 	(void)av;
// 	while (i < 2)
// 	{
// 		pipe(pipefd);
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			return (1);
// 		}
// 		if (pid == 0)
// 		{
// 			dup2(pipefd[1], STDOUT_FILENO);
// 			close(pipefd[0]);
// 			close(pipefd[1]);
// 			if (i == 0)
// 				execve(cmd1[0], cmd1, NULL);
// 			else if (i == 1)
// 				execve(cmd2[0], cmd2, NULL);
// 			perror("execve");
// 			return (EXIT_FAILURE);
// 		}
// 		else
// 		{
// 			dup2(pipefd[0], STDIN_FILENO);
// 			close(pipefd[0]);
// 			close(pipefd[1]);
// 		}
// 		i++;
// 	}
// 	pid = fork();
// 	if (pid== 0)
// 	{
// 		execve(cmd3[0], cmd3, NULL);
// 		perror("execve");
// 		return (EXIT_FAILURE);
// 	}
// 	i = 0;
// 	while (i < 3)
// 	{
// 		waitpid(pid, &status, 0);
// 		i++;
// 	}
// }


static void	print_strs(char **strs)
{
	int i = 0;

	while (strs[i] != NULL)
	{
		printf("%d: ", i);
		printf("%s\n", strs[i]);
		i++;
	}
}

void	print_data(t_input_data *data)
{
	int i = 0;

	printf("infile: %s\n", data->infile);
	printf("outfile: %s\n", data->outfile);
	while (data->cmds[i] != NULL)
	{
		printf("cmd[%d]:\n", i);
		print_strs(data->cmds[i]);
		i++;
	}
}

static void	test_valid_data(t_input_data *data, int test)
{
	if (data->infile != NULL && data->outfile != NULL && data->cmds != NULL)
	{
		printf(GREEN "Test %d: SUCCESS\n" WHITE, test);
		print_data(data);
	}
	else
		printf(RED "Test %d: FAILURE\n" WHITE, test);
}


int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_input_data	*data;
	t_input_data	*data2;
	t_input_data	*data3;

	char *av1[] = {"pipex", "test1", "cmd1", "cmd2", "test2", NULL};
	char *av2[] = {"pipex", "test1", "ls", "grep", "wc", "echo3", NULL};
	char *av3[] = {"pipex", "test1", "a", "ls -l", "sleep 3", "echo3", NULL};

	data = get_files_and_commands(av1 + 1, env);
	data2 = get_files_and_commands(av2 + 1, env);
	data3 = get_files_and_commands(av3 + 1, env);

	if (data != NULL)
	{
		test_valid_data(data, 1);
		free_data(data);
	}
	if (data2 != NULL)
	{
		test_valid_data(data2, 2);
		free_data(data2);
	}
	if (data3 != NULL)
	{
		test_valid_data(data3, 3);
		free_data(data3);
	}
}
