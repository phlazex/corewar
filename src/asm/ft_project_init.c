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

int		ft_parse_file_dis(t_mem *mem, t_project *project)
{
	project->data = mem;
	project->name = mem->head + 4;
	project->prog_size = project->name + PROG_NAME_LENGTH + 4;
	project->comment = project->prog_size + 4;
	project->program = project->comment + COMMENT_LENGTH + 4;
	project->end = mem->end;
	return (0);
}

int		ft_project_init(t_project *project,
		int (*ft_parse)(t_mem *, t_project *))
{
	t_mem	*data;

	project->fd = open(project->file_name, O_RDONLY);
	if (!(data = ft_init_memory()))
	{
		close(project->fd);
		ft_exit(project, 2, NULL);
	}
	if (fast_read_in_memory(project->fd, data))
	{
		close(project->fd);
		ft_free_mem(data);
		ft_exit(project, 1, NULL);
	}
	close(project->fd);
	return (((*ft_parse)(data, project)));
}
