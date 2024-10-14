/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:12:23 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/13 17:38:36 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_state_function	resolve_pipex(int ac, char **av, char **env)
{
	t_input_data	*data;

	if (ac < 4)
	{
		ft_putendl_fd("Error: not enough arguments", STDERR_FILENO);
		return (FAILURE);
	}
	data = get_files_and_cmds_from_strs(ac, (const char **)av);
	if (data == NULL)
	{
		ft_putendl_fd("Error: failed data malloc", STDERR_FILENO);
		return (FAILURE);
	}
	if (data->infile == NULL)
	{
		ft_putendl_fd("Error: invalid input file", STDERR_FILENO);
		free_data(data);
		return (FAILURE);
	}
	if (exec_cmds_with_files(data, env) != SUCCESS)
	{
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
