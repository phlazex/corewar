/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prog_list_getters_args.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 15:30:48 by mfahey            #+#    #+#             */
/*   Updated: 2020/07/01 15:35:02 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int ft_get_num_label(t_project *project, size_t arg_num)
{
	int	num;

	num = 0;
	if (project->current_list->arg_label_list_ptr[arg_num] < project->current_list)
	{
		num = ft_get_prev_num_label(project, arg_num);
	}
	else
	{
		num = ft_get_next_num_label(project, arg_num);
	}
	return (num);
}

static void ft_get_arg_ind(t_project *project, size_t *i, size_t arg_num)
{
	int		num;

	if (project->current_list->arg_label_list_ptr[arg_num])
	{
		num = ft_get_num_label(project, arg_num);
	}
	else
	{
		num = ft_atoi(project->current_list->args[arg_num]);
	}
	ft_get_two_bytes(project->current_list->code_line, i, num);
}

static void ft_get_arg_dir(t_project *project, size_t *i, size_t arg_num)
{
	int		num;

	if (project->current_list->arg_label_list_ptr[arg_num])
	{
		num = ft_get_num_label(project, arg_num);
	}
	else
	{
		num = ft_atoi(project->current_list->args[arg_num] + 1);
	}
	if (g_op_tab[project->current_list->command_num].dir_size == DIR_SIZE)
	{
		ft_get_four_bytes(project->current_list->code_line, i, num);
	}
	else if (g_op_tab[project->current_list->command_num].dir_size == IND_SIZE)
	{
		ft_get_two_bytes(project->current_list->code_line, i, num);
	}
}

void ft_get_args(t_project *project, size_t *i)
{
	size_t	j;

	j = 0;
	while (j < g_op_tab[project->current_list->command_num].arg_count)
	{
		if (project->current_list->args_code[j] == REG_CODE)
		{
			project->current_list->code_line[(*i)++] = ft_atoi(project->current_list->args[j] + 1);
		}
		else if (project->current_list->args_code[j] == DIR_CODE)
		{
			ft_get_arg_dir(project, i, j);
		}
		else if (project->current_list->args_code[j] == IND_CODE)
		{
			ft_get_arg_ind(project, i, j);
		}
		j++;
	}
}
