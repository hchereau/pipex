/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:28:25 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/07 15:05:10 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	init_cmds(t_cmd **cmds, size_t	strs_len)
{
	*cmds = (t_cmd *)malloc(sizeof(t_cmd) * (strs_len));
}

static void	get_cmd(t_cmd **cmd, const char *str)
{
	(*cmd)->cmd = ft_split(str, ' ');
}

t_state_function	get_cmds(t_cmd	**cmds, const char **strs)
{
	size_t	i;

	i = 0;
	init_cmds(cmds, ft_strslen(strs));
	if (cmds == NULL)
		return (SUCCESS);
	while (strs[i + 1] != NULL)
	{
		get_cmd(cmds, *strs);
		if (cmds[i]->cmd == NULL)
			return (FAILURE);
		++i;
	}
	return (SUCCESS);
}
