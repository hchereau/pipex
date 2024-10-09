/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:42:02 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/09 11:04:15 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "libft.h"
# include "parsing.h"
# include "exec.h"

typedef enum e_state_function
{
	ERROR = -1,
	FAILURE,
	SUCCESS
}	t_state_function;

typedef struct s_cmd
{
	char	**cmd;
	int		fd_in;
	int		fd_out;
}	t_cmd;

typedef struct s_input_data
{
	t_cmd	*cmds;
	char	*infile;
	char	*outfile;
}	t_input_data;

void	free_data(t_input_data *data);
void	free_cmds(t_cmd *cmds);

#endif
