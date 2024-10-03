/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_malloc_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:25:32 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/03 10:26:14 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_malloc_str(char *str)
{
	char	*new_str;

	new_str = ft_strdup(str);
	if (new_str == NULL)
	{
		ft_putendl_fd("Error: malloc failed in get_malloc_str", STDERR_FILENO);
		return (NULL);
	}
	return (new_str);
}
