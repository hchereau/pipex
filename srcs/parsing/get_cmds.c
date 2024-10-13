/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:28:25 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/13 16:27:00 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	init_cmds(t_cmd **cmds, size_t	strs_len)
{
	*cmds = (t_cmd *)malloc(sizeof(t_cmd) * (strs_len));
}

static void	get_cmd(t_cmd *cmd, const char *str)
{
	cmd->tokens = ft_split(str, ' ');
}

t_cmd	*build_cmds(const char **strs, int strs_len, bool is_not_here_doc)
{
	t_cmd	*cmds;
	size_t	i_strs;
	size_t	i_cmds;

	i_cmds = 0;
	i_strs = is_not_here_doc;
	strs_len -= is_not_here_doc;
	init_cmds(&cmds, strs_len);
	if (cmds == NULL)
		return (NULL);
	while (strs[i_strs + 1] != NULL)
	{
		get_cmd(&cmds[i_cmds], strs[i_strs]);
		if (cmds[i_cmds].tokens == NULL)
		{
			free_cmds(cmds);
			return (NULL);
		}
		++i_strs;
		++i_cmds;
	}
	cmds[i_cmds].tokens = NULL;
	return (cmds);
}
