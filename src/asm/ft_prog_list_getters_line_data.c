/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prog_list_getters_line_data.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 15:33:59 by mfahey            #+#    #+#             */
/*   Updated: 2020/07/01 15:36:26 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_get_next_num_label(t_project *project, size_t arg_num)
{
	t_prog_list	*next_prog_list;
	int			num;

	num = 0;
	next_prog_list = project->current_list;
	while (next_prog_list)
	{
		if (next_prog_list ==
				project->current_list->arg_label_list_ptr[arg_num])
			break ;
		num += next_prog_list->command_size;
		next_prog_list = next_prog_list->next_list;
	}
	return (num);
}

int		ft_get_prev_num_label(t_project *project, size_t arg_num)
{
	t_prog_list	*prev_prog_list;
	int			num;

	num = 0;
	prev_prog_list = project->current_list->prev_list;
	while (prev_prog_list)
	{
		num += prev_prog_list->command_size;
		if (prev_prog_list ==
				project->current_list->arg_label_list_ptr[arg_num])
			break ;
		prev_prog_list = prev_prog_list->prev_list;
	}
	return (-num);
}

void	ft_get_four_bytes(char *str, size_t *i, int num)
{
	str[(*i)++] = (num >> 24) & 0xff;
	str[(*i)++] = (num >> 16) & 0xff;
	str[(*i)++] = (num >> 8) & 0xff;
	str[(*i)++] = num & 0xff;
}

void	ft_get_two_bytes(char *str, size_t *i, int num)
{
	str[(*i)++] = (num >> 8) & 0xff;
	str[(*i)++] = num & 0xff;
}
