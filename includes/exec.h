/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:24:23 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/09 15:29:47 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "pipex.h"

# define WAIT_PIPEFD -1

typedef struct s_input_data		t_input_data;
typedef enum e_state_function	t_state_function;
typedef struct s_cmd			t_cmd;

t_state_function	exec_cmds_with_files(t_input_data	*data, char **env);
t_state_function	manages_fd_cmds(t_cmd *cmds, const char *path_infile,
						const char *path_outfile);
char				*get_path_cmds(char **env, char *cmd);
t_state_function	exec_cmds(t_cmd *cmds, char **env);
#endif
