/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:28:25 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/08 15:17:35 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	init_cmds(t_cmd **cmds, size_t	strs_len)
{
	*cmds = (t_cmd *)malloc(sizeof(t_cmd) * (strs_len));
}

static void	get_cmd(t_cmd *cmd, const char *str)
{
	cmd->cmd = ft_split(str, ' ');
}

t_cmd	*get_cmds(const char **strs, const int strs_len)
{
	t_cmd	*cmds;
	size_t	i;

	i = 0;
	init_cmds(&cmds, strs_len);
	if (cmds == NULL)
		return (NULL);
	while (strs[i + 1] != NULL)
	{
		get_cmd(&cmds[i], strs[i]);
		if (cmds[i].cmd == NULL)
		{
			free_cmds(cmds);
			return (NULL);
		}
		++i;
	}
	cmds[i].cmd = NULL;
	return (cmds);
}
