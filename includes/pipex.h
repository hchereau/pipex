/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:42:02 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/03 14:03:22 by hucherea         ###   ########.fr       */
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
	FAILURE = -1,
	SUCCESS
}	t_state_function;

typedef struct s_input_data
{
	char	***cmds;
	char	*infile;
	char	*outfile;
}	t_input_data;

void	free_data(t_input_data *data);
void	free_cmds(char ***cmds);

#endif
