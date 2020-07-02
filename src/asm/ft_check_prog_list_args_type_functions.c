/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_prog_list_args_type_functions.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:39:08 by mfahey            #+#    #+#             */
/*   Updated: 2020/07/02 17:41:28 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_is_valid_label(t_project *project, char *label, size_t arg_num)
{
	t_prog_list	*prog_list;

	prog_list = project->prog_list;
	while (prog_list)
	{
		if (prog_list->label)
		{
			if (!ft_strcmp(prog_list->label, label) &&
					!project->current_list->arg_label_list_ptr[arg_num])
				project->current_list->arg_label_list_ptr[arg_num] = prog_list;
			else if (!ft_strcmp(prog_list->label, label) &&
					project->current_list->arg_label_list_ptr[arg_num])
				return (0);
		}
		prog_list = prog_list->next_list;
	}
	if (!project->current_list->arg_label_list_ptr[arg_num])
		return (0);
	return (1);
}

int		ft_is_arg_func(t_project *project, size_t arg_num,
		size_t command_size, size_t arg_code)
{
	project->current_list->command_size += command_size;
	project->current_list->args_code[arg_num] = arg_code;
	return (1);
}

int		ft_is_ind_dir_func(t_project *project, size_t arg_num, size_t i)
{
	size_t		len;

	if (project->current_list->args[arg_num][--i] == '-')
		i++;
	len = ft_strlen(project->current_list->args[arg_num]);
	while (i < len)
		if (ft_isdigit(project->current_list->args[arg_num][i++]) < 0)
			return (0);
	return (1);
}
