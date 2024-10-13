/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:24:23 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/13 17:03:11 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "pipex.h"

# define WAIT_PIPEFD -2
# define ERROR_DUP2 -1
# define INDEX_FIRST_CMD 0

typedef struct s_input_data		t_input_data;
typedef enum e_state_function	t_state_function;
typedef struct s_cmd			t_cmd;

t_state_function	exec_cmds_with_files(t_input_data	*data, char **env);
t_state_function	manages_fd_cmds(t_cmd	*cmds, const char *infile,
						const char *outfile, size_t i);
char				*get_path_cmds(char **env, char *cmd);
t_state_function	exec_cmds(t_cmd *cmds, char **env, const char *infile,
						const char *outfile);
#endif
