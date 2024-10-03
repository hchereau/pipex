/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:24:23 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/03 15:13:27 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "pipex.h"

typedef struct s_input_data		t_input_data;
typedef enum e_state_function	t_state_function;

void	exec_pipex(t_input_data *data);
void	exec_commands(char *infile, char ***cmds, int *pid);
void	exec_last_command(char **cmd, char *outfile, int *pid);

#endif
