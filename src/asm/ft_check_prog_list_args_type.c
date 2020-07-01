/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_prog_list_args_type.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 15:21:17 by mfahey            #+#    #+#             */
/*   Updated: 2020/07/01 15:23:41 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int 	ft_is_valid_label(t_project *project, char *label, size_t arg_num)
{
	t_prog_list	*prog_list;

	prog_list = project->prog_list;
	while (prog_list)
	{
		if (prog_list->label)
		{
			if (!ft_strcmp(prog_list->label, label) && !project->current_list->arg_label_list_ptr[arg_num])
			{
				project->current_list->arg_label_list_ptr[arg_num] = prog_list;
			}
			else if (!ft_strcmp(prog_list->label, label) && project->current_list->arg_label_list_ptr[arg_num])
			{
				return (0);
			}
		}
		prog_list = prog_list->next_list;
	}
	if (!project->current_list->arg_label_list_ptr[arg_num])
	{
		return (0);
	}
	return (1);
}

int	ft_is_ind(t_project *project, size_t arg_num)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (project->current_list->args[arg_num][i++] == LABEL_CHAR)
	{
		if (ft_is_label_command(project->current_list->args[arg_num] + i, 0) && ft_is_valid_label(project, project->current_list->args[arg_num] + i, arg_num))
		{
			project->current_list->command_size += IND_SIZE;
			project->current_list->args_code[arg_num] = IND_CODE;
			return (1);
		}
	}
	else
	{
		if (project->current_list->args[arg_num][--i] == '-')
		{
			i++;
		}
		len = ft_strlen(project->current_list->args[arg_num]);
		while (i < len)
		{
			if (ft_isdigit(project->current_list->args[arg_num][i++]) < 0)
			{
				return (0);
			}
		}
		project->current_list->command_size += IND_SIZE;
		project->current_list->args_code[arg_num] = IND_CODE;
		return (1);
	}
	return (0);
}

int	ft_is_dir(t_project *project, size_t arg_num)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (project->current_list->args[arg_num][i++] == DIRECT_CHAR)
	{
		if (project->current_list->args[arg_num][i++] == LABEL_CHAR)
		{
			if (ft_is_label_command(project->current_list->args[arg_num] + i, 0) && ft_is_valid_label(project, project->current_list->args[arg_num] + i, arg_num))
			{
				project->current_list->command_size += g_op_tab[project->current_list->command_num].dir_size;
				project->current_list->args_code[arg_num] = DIR_CODE;
				return (1);
			}
		}
		else
		{
			if (project->current_list->args[arg_num][--i] == '-')
			{
				i++;
			}
			len = ft_strlen(project->current_list->args[arg_num]);
			while (i < len)
			{
				if (ft_isdigit(project->current_list->args[arg_num][i++]) < 0)
				{
					return (0);
				}
			}
			project->current_list->command_size += g_op_tab[project->current_list->command_num].dir_size;
			project->current_list->args_code[arg_num] = DIR_CODE;
			return (1);
		}
	}
	return (0);
}

int	ft_is_reg(t_project *project, size_t arg_num)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (project->current_list->args[arg_num][i++] == 'r' && (len = ft_strlen(project->current_list->args[arg_num])) <= 3)
	{
		while (i < len)
		{
			if (ft_isdigit(project->current_list->args[arg_num][i++]) < 0)
			{
				return (0);
			}
		}
		if (ft_atoi(project->current_list->args[arg_num] + 1) > 0)
		{
			project->current_list->command_size += 1;
			project->current_list->args_code[arg_num] = REG_CODE;
			return (1);
		}
	}
	return (0);
}
