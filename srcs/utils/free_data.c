/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:45:03 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/02 16:12:58 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_data(t_input_data *data)
{

	if (data->cmd)
		free_strs(data->cmd);
	if (data->infile)
		free(data->infile);
	if (data->outfile)
		free(data->outfile);
	free(data);
}
