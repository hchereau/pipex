/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:45:03 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/07 13:49:12 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_data(t_input_data *data)
{

	if (data->cmds != NULL)
		free_cmds(data->cmds);
	if (data->infile != NULL)
		free(data->infile);
	if (data->outfile != NULL)
		free(data->outfile);
	free(data);
}
