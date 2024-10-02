/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:12:16 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/02 16:11:43 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "pipex.h"

# define ENV_PATH "PATH="
# define SIZE_ENV_PATH 5

typedef struct s_input_data		t_input_data;
typedef enum e_state_fonction	t_state_fonction;

t_input_data	*get_files_and_commands(char **strs, char **env);
char			**get_commands(char **strs, char **env);
void			print_data(t_input_data *data);

#endif
