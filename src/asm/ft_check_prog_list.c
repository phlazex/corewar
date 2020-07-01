/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_prog_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 14:53:02 by mfahey            #+#    #+#             */
/*   Updated: 2020/07/01 14:59:19 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_check_command_name(t_project *project)
{
	size_t	i;

	i = 0;
	while (i < MAX_OP)
	{
		if (!ft_strcmp(project->current_list->command, g_op_tab[i].name))
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

static int 	ft_check_prog_list_line(t_project *project)
{
	int	cmd_num;

	if (project->current_list->command)
	{
		cmd_num = 0;
		if ((cmd_num = ft_check_command_name(project)) < 0)
		{
			return (0);
		}
		project->current_list->command_num = cmd_num;
		project->current_list->command_size = 1 + g_op_tab[project->current_list->command_num].arg_type;
		if (!(ft_check_count_args(project) && ft_check_args(project)))
		{
			return (0);
		}
	}
	return (1);
}

int 	ft_check_prog_list(t_project *project)
{
	project->current_list = project->prog_list;
	while (project->current_list)
	{
//		ft_printf("\n%zi", project->current_list->num_line);
		if (!ft_check_prog_list_line(project))
		{
			return (0);
		}
		project->size_program += project->current_list->command_size;
		project->current_list = project->current_list->next_list;
	}
	return (1);
}
