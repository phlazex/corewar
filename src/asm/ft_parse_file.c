/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:43:49 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/30 13:44:42 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_parse_file_check(t_project *project)
{
	if ((!project->name || ft_strlen(project->name) > PROG_NAME_LENGTH) ||
			(!project->comment || ft_strlen(project->comment) > COMMENT_LENGTH))
	{
		if (!project->name && !project->comment)
			ft_exit(project, 6, NULL);
		else if (ft_strlen(project->name) > PROG_NAME_LENGTH)
			ft_exit(project, 5, NAME_CMD_STRING);
		else if (ft_strlen(project->comment) > COMMENT_LENGTH)
			ft_exit(project, 5, COMMENT_CMD_STRING);
		else
			ft_exit(project, 3, NULL);
	}
	else
	{
		if (!ft_check_prog_list(project))
		{
			project->num_error_line = project->current_list->num_line;
			ft_exit(project, 7, NULL);
		}
		ft_get_program_line(project);
	}
}

static void	ft_parse_file_project_init(t_mem *mem, t_project *project)
{
	project->data = mem;
	project->current = mem->head;
	project->end = mem->end;
	project->size_program = 0;
	project->name = NULL;
	project->comment = NULL;
	project->program = NULL;
	project->prog_list = NULL;
	project->num_current_line = 0;
	project->num_error = 0;
	project->num_error_line = 0;
}

int			ft_parse_file(t_mem *mem, t_project *project, char *file)
{
	ft_parse_file_project_init(mem, project);
	if ((mem->endl = ft_strchr(mem->head, '\n')))
	{
		mem->current = mem->head;
		while (mem->current < mem->end)
		{
			project->num_current_line++;
			if ((mem->endl = ft_strchr(mem->current, '\n')))
			{
				ft_parse_current(project);
				mem->current = mem->endl + 1;
			}
			else if ((mem->endl = ft_strchr(mem->current, '\0')))
			{
				ft_parse_current(project);
				mem->current = mem->end;
			}
		}
	}
	ft_parse_file_check(project);
	ft_write_to_file(project, file);
	return (0);
}
