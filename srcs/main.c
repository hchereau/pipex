/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:12:23 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/13 16:36:16 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	is_not_enough_args(int ac, char *cmd)
{
	if (ft_strncmp(cmd, "here_doc", LEN_HERE_DOC) == 0 && ac < 5)
	{
		ft_putendl_fd("Usage: here_doc LIMITER cmd1 cmd2 ... cmdn outfile",
			STDERR_FILENO);
		return (true);
	}
	else if (ac < 4)
	{
		ft_putstr_fd("Usage: ", STDERR_FILENO);
		ft_putendl_fd(" infile cmd1 cmd2 ... cmdn outfile", STDERR_FILENO);
		return (true);
	}
	return (false);
}

t_state_function	resolve_pipex(int ac, char **av, char **env)
{
	t_input_data	*data;

	if (is_not_enough_args(ac, av[0]) == true)
	{
		ft_putendl_fd("Error: not enough arguments", STDERR_FILENO);
		return (FAILURE);
	}
	else
	{
		data = get_files_and_cmds_from_strs(ac, (const char **)av);
		if (data->infile == NULL)
		{
			ft_putendl_fd("Error: invalid input file", STDERR_FILENO);
			free_data(data);
			return (FAILURE);
		}
		if (exec_cmds_with_files(data, env) != SUCCESS)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	if (resolve_pipex(ac - 1, av + 1, env) == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
