/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:12:23 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/03 11:06:33 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_state_fonction	resolve_pipex(int ac, char **av, char **env)
{
	t_input_data	*data;

	if (ac < 4)
	{
		ft_putendl_fd("Error: usage ./pipex file1 cmd1 cmd2 .... file2",
			STDERR_FILENO);
		return (FAILURE);
	}
	data = get_file_and_commands(av, env);
	if (data != NULL)
	{
		exec_pipex(data);
		free_data(data);
	}
	if (data->infile == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	if (resolve_pipex(ac - 1, av + 1, env) == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
