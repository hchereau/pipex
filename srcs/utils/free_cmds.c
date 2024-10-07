/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:53:38 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/07 14:42:55 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmds(t_cmd *cmds)
{
	while(cmds->cmd != NULL)
	{
		free_strs(cmds->cmd);
		++cmds;
	}
	free(cmds);
}
