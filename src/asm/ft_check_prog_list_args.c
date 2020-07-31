/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_prog_list_args.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 15:11:14 by mfahey            #+#    #+#             */
/*   Updated: 2020/07/01 15:15:14 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_check_arg_first(
		t_project *project, size_t arg_num, size_t size_type)
{
	if (size_type == 5)
	{
		if (!(ft_is_reg(project, arg_num) || ft_is_ind(project, arg_num)))
			return (0);
	}
	else if (size_type == 6)
	{
		if (!(ft_is_dir(project, arg_num) || ft_is_ind(project, arg_num)))
			return (0);
	}
	else if (size_type == 7)
	{
		if (!(ft_is_reg(project, arg_num) || ft_is_dir(project, arg_num) ||
				ft_is_ind(project, arg_num)))
			return (0);
	}
	return (1);
}

static int	ft_check_arg(t_project *project, size_t arg_num)
{
	size_t	size_type;

	size_type = 0;
	if ((size_type =
			g_op_tab[project->current_list->command_num].types[arg_num]) == 1)
	{
		if (!ft_is_reg(project, arg_num))
			return (0);
	}
	else if (size_type == 2)
	{
		if (!ft_is_dir(project, arg_num))
			return (0);
	}
	else if (size_type == 3)
	{
		if (!(ft_is_reg(project, arg_num) || ft_is_dir(project, arg_num)))
			return (0);
	}
	else
		return (ft_check_arg_first(project, arg_num, size_type));
	return (1);
}

int			ft_check_args(t_project *project)
{
	size_t	i;

	i = 0;
	while (i < g_op_tab[project->current_list->command_num].arg_count)
	{
		if (!ft_check_arg(project, i))
			return (0);
		i++;
	}
	return (1);
}

int			ft_check_count_args(t_project *project)
{
	int		i;

	i = 0;
	if (project->current_list->args[0])
		i++;
	if (project->current_list->args[1])
		i++;
	if (project->current_list->args[2])
		i++;
	if (i == g_op_tab[project->current_list->command_num].arg_count)
		return (1);
	project->code_error = WRONG_ARGUMENT_NUMBER;
	return (0);
}
