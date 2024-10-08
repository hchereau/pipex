/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:12:16 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/08 15:02:04 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "pipex.h"

# define ENV_PATH "PATH="
# define SIZE_ENV_PATH 5
# define INDEX_INFILE 0

typedef struct s_input_data		t_input_data;
typedef enum e_state_function	t_state_function;
typedef struct s_cmd			t_cmd;

t_state_function	get_files(char **infile, char **outfile, const char **strs,
						const int strs_len);
t_cmd				*get_cmds(const char **strs, const int strs_len);
t_input_data		*get_files_and_cmds_from_strs(int strs_len,
						const char **strs);
#endif
