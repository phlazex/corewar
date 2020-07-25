/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_project_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 19:18:04 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/22 19:18:05 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_parse_file_dis(t_mem *mem, t_project *project, char *file)
{
	project->data = mem;
	project->name = mem->head + 4;
	project->prog_size = project->name + PROG_NAME_LENGTH + 4;
	project->comment = project->prog_size + 4;
	project->program = project->comment + COMMENT_LENGTH + 4;
	project->end = mem->end;
	project->file_name = file;
	return (0);
}

int		ft_project_init(char *file_name, t_project **project,
		int (*ft_parse)(t_mem *, t_project *, char *))
{
	int		fd;
	t_mem	*data;

	fd = open(file_name, O_RDONLY);
	if (!(*project = (t_project*)malloc(sizeof(**project))))
	{
		close(fd);
		ft_exit(NULL, 2, NULL);
	}
	data = ft_init_memory();
	if (fast_read_in_memory(fd, data))
	{
		close(fd);
		ft_free_mem(data);
		ft_exit(NULL, 1, NULL);
	}
	close(fd);
	ft_bzero(*project, sizeof(**project));
	return (((*ft_parse)(data, *project, file_name)));
}
