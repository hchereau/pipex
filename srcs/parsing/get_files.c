/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:10:59 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/12 12:12:10 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_state_function	get_infile(char **infile, const char *str)
{
	if (ft_strncmp(str, "here_doc", LEN_HERE_DOC) == 0)
	{
		get_here_doc(infile);
	}
	else
	{
		*infile = ft_strdup(str);
		if (*infile == NULL)
			return (FAILURE);
		return (SUCCESS);
	}
}

static t_state_function	get_outfile(char **outfile, const char *str)
{
	*outfile = ft_strdup(str);
	if (*outfile == NULL)
		return (FAILURE);
	return (SUCCESS);
}

t_state_function	get_files(char **infile, char **outfile, const char **strs,
	const int strs_len)
{
	if (get_infile(infile, strs[INDEX_INFILE]) == FAILURE)
		return (FAILURE);
	return (get_outfile(outfile, strs[strs_len - 1]));
}
