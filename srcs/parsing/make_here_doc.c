/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea <hucherea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:25:21 by hucherea          #+#    #+#             */
/*   Updated: 2024/10/13 20:43:51 by hucherea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <string.h>

static void	create_here_doc(int *fd)
{
	*fd = open(FILE_TEMP_HERE_DOC, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
	{
		ft_putendl_fd("Error: open failed", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

static void	fill_here_doc(int fd, const char *end_here_doc)
{
	char	*line;
	char	*str_end_here_doc;

	str_end_here_doc = ft_strjoin(end_here_doc, "\n");
	ft_putstr_fd("here_doc> ", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (line && strcmp(str_end_here_doc, line))
	{
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	free(str_end_here_doc);
}

void	make_here_doc_file(char **infile, const char *end_here_doc)
{
	int	fd;

	create_here_doc(&fd);
	fill_here_doc(fd, end_here_doc);
	close(fd);
	*infile = ft_strdup(FILE_TEMP_HERE_DOC);
}
