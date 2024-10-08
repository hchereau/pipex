/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:24:23 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/08 17:12:14 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "pipex.h"

typedef struct s_input_data		t_input_data;
typedef enum e_state_function	t_state_function;

t_state_function	exec_cmds_with_files(t_data	*data, char **env);

#endif
