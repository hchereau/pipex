/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:53:38 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/08 15:38:26 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmds(t_cmd *cmds)
{
	size_t	i;

	i = 0;
	while(cmds[i].cmd != NULL)
	{
		free_strs(cmds[i].cmd);
		++i;
	}
	free(cmds);
}
