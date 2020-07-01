/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prog_list_getters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 15:00:53 by mfahey            #+#    #+#             */
/*   Updated: 2020/07/01 15:06:06 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int ft_get_code_line(t_project *project)
{
	size_t	i;

	if (!(project->current_list->code_line = ft_strnew(project->current_list->command_size + 1)))
	{
		return (0);
	}
	i = 0;
	project->current_list->code_line[i++] = g_op_tab[project->current_list->command_num].id;
	if (g_op_tab[project->current_list->command_num].arg_type)
	{
		project->current_list->code_line[i++] = (project->current_list->args_code[0] << 6) + (project->current_list->args_code[1] << 4) + (project->current_list->args_code[2] << 2);
	}
	ft_get_args(project, &i);
	project->current_list->code_line[i] = 0;
	return (1);
}

int 	ft_get_program_line(t_project *project)
{
	size_t	i;
	size_t	length;

	length = (size_t)(sizeof(int) * 4 + COMMENT_LENGTH + PROG_NAME_LENGTH + project->size_program);
	project->program = ft_strnew(length + 1);
	project->program = ft_memset(project->program, 0, length + 1);
	i = 0;
	ft_get_four_bytes(project->program, &i, COREWAR_EXEC_MAGIC);
	ft_strncpy(project->program + i, project->name, PROG_NAME_LENGTH);
	i += PROG_NAME_LENGTH;
	ft_get_four_bytes(project->program, &i, 0);
	ft_get_four_bytes(project->program, &i, project->size_program);
	ft_strncpy(project->program + i, project->comment, COMMENT_LENGTH);
	i += COMMENT_LENGTH;
	ft_get_four_bytes(project->program, &i, 0);
	project->current_list = project->prog_list;
	while (project->current_list)
	{
		if (!ft_get_code_line(project))
		{
			return (0);
		}
		ft_memcpy(project->program + i, project->current_list->code_line, project->current_list->command_size);
		i += project->current_list->command_size;
		project->current_list = project->current_list->next_list;
	}
//	size_t	z = 0;
//	while (z < length)
//	{
//		ft_printf("%c", project->program[z++]);
//		ft_printf("%zi ", project->program[z++]);
//		ft_printf("%x ", project->program[z++]);
//	}
	return (1);
}
