/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:45:03 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/03 12:54:29 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_data(t_input_data *data)
{

	if (data->cmd)
		free_cmds(data->cmd);
	if (data->infile)
		free(data->infile);
	if (data->outfile)
		free(data->outfile);
	free(data);
}
