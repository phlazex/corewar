/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 19:41:23 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/22 19:41:26 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_free_mem(t_mem *data)
{
	if (data)
	{
		data->current = NULL;
		data->end = NULL;
		data->endl = NULL;
		if (data->head)
			ft_strdel(&(data->head));
		ft_memdel((void **)&(data));
	}
}

static void	ft_free_prog_list(t_project *project)
{
	project->current_list->line_ptr = NULL;
	project->current_list->endl_ptr = NULL;
	if (project->current_list->new_line)
		ft_strdel(&(project->current_list->new_line));
	if (project->current_list->label)
		ft_strdel(&(project->current_list->label));
	if (project->current_list->command)
		ft_strdel(&(project->current_list->command));
	if (project->current_list->args[0])
		ft_strdel(&(project->current_list->args[0]));
	if (project->current_list->args[1])
		ft_strdel(&(project->current_list->args[1]));
	if (project->current_list->args[2])
		ft_strdel(&(project->current_list->args[2]));
	if (project->current_list->code_line)
		ft_strdel(&(project->current_list->code_line));
	project->current_list->arg_label_list_ptr[0] = NULL;
	project->current_list->arg_label_list_ptr[1] = NULL;
	project->current_list->arg_label_list_ptr[2] = NULL;
}

static void	ft_free_prog_lists(t_project *project)
{
	if (project->prog_list)
	{
		project->current_list = project->prog_list;
		while (project->current_list)
		{
			ft_free_prog_list(project);
			project->prog_list = project->current_list;
			project->current_list = project->current_list->next_list;
			if (project->prog_list)
			{
				project->prog_list->prev_list = NULL;
				project->prog_list->next_list = NULL;
				ft_memdel((void **)&(project->prog_list));
			}
		}
	}
}

static void	ft_free_project(t_project *project)
{
	if (project->route > 0)
	{
		if (project->name)
			ft_strdel(&(project->name));
		if (project->comment)
			ft_strdel(&(project->comment));
		if (project->program)
			ft_strdel(&(project->program));
	}
	project->prog_size = NULL;
	project->current = NULL;
	project->end = NULL;
	ft_memdel((void **)&(project));
}

void		ft_free(t_project *project)
{
	if (project)
	{
		ft_free_mem(project->data);
		ft_free_prog_lists(project);
		ft_free_project(project);
	}
}
