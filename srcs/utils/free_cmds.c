/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:53:38 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/09 16:01:15 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmds(t_cmd *cmds)
{
	size_t	i;

	i = 0;
	while (cmds[i].tokens != NULL)
	{
		free_strs(cmds[i].tokens);
		++i;
	}
	free(cmds);
}
