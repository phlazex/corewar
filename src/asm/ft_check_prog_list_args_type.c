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

int		ft_is_ind(t_project *project, size_t arg_num)
{
	size_t	i;

	i = 0;
	if (project->current_list->args[arg_num][i++] == LABEL_CHAR)
	{
		if (ft_is_label_command(
				project->current_list->args[arg_num] + i,
				0) && ft_is_valid_label(project,
				project->current_list->args[arg_num] + i, arg_num))
			return (ft_is_arg_func(project, arg_num, IND_SIZE, IND_CODE));
	}
	else
	{
		if (!ft_is_ind_dir_func(project, arg_num, i))
			return (0);
		return (ft_is_arg_func(project, arg_num, IND_SIZE, IND_CODE));
	}
	project->code_error = WRONG_ARGUMENT_TYPE;
	return (0);
}

int		ft_is_dir(t_project *project, size_t arg_num)
{
	size_t	i;

	i = 0;
	if (project->current_list->args[arg_num][i++] == DIRECT_CHAR)
	{
		if (project->current_list->args[arg_num][i++] == LABEL_CHAR)
		{
			if (ft_is_label_command(project->current_list->args[arg_num] + i,
					0) && ft_is_valid_label(project,
					project->current_list->args[arg_num] + i, arg_num))
				return (ft_is_arg_func(project, arg_num,
						g_op_tab[project->current_list->command_num].dir_size,
						DIR_CODE));
		}
		else
		{
			if (!ft_is_ind_dir_func(project, arg_num, i))
				return (0);
			return (ft_is_arg_func(project, arg_num,
					g_op_tab[project->current_list->command_num].dir_size,
					DIR_CODE));
		}
	}
	project->code_error = WRONG_ARGUMENT_TYPE;
	return (0);
}

int		ft_is_reg(t_project *project, size_t arg_num)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (project->current_list->args[arg_num][i++] == 'r' &&
			(len = ft_strlen(project->current_list->args[arg_num])) <= 3)
	{
		while (i < len)
			if (ft_isdigit(project->current_list->args[arg_num][i++]) < 0)
				return (0);
		if (ft_atoi(project->current_list->args[arg_num] + 1) > 0)
			return (ft_is_arg_func(project, arg_num, 1, REG_CODE));
	}
	project->code_error = WRONG_ARGUMENT_TYPE;
	return (0);
}
