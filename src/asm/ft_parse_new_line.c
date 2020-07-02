/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_new_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:22:21 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/30 15:25:56 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_parse_new_line_else(t_prog_list *prog_list, size_t *i)
{
	size_t	j;

	j = 0;
	while ((prog_list->new_line)[*i] != '\0' &&
			(prog_list->new_line)[*i] != SEPARATOR_CHAR)
	{
		j++;
		(*i)++;
	}
	if (ft_get_new_word(prog_list, *i, j))
		return (1);
	if ((prog_list->new_line)[*i] == SEPARATOR_CHAR)
		(*i)++;
	return (0);
}

static int	ft_parse_new_line_if(t_prog_list *prog_list, size_t *i)
{
	size_t	j;

	j = 0;
	while ((prog_list->new_line)[*i] != '\0' &&
			ft_is_labels_char((prog_list->new_line)[*i], 0))
	{
		j++;
		(*i)++;
	}
	if ((prog_list->new_line)[*i] == LABEL_CHAR &&
			!prog_list->label && !prog_list->command)
	{
		j++;
		(*i)++;
	}
	if (ft_get_new_word(prog_list, *i, j))
		return (1);
	while ((prog_list->new_line)[*i] != '\0' &&
			ft_isspace((prog_list->new_line)[*i]))
		(*i)++;
	return (0);
}

static void	ft_parse_new_line_prog_list_init(t_prog_list *prog_list)
{
	prog_list->label = NULL;
	prog_list->command = NULL;
	prog_list->args[0] = NULL;
	prog_list->args[1] = NULL;
	prog_list->args[2] = NULL;
	prog_list->command_size = 0;
	prog_list->command_num = 0;
	prog_list->arg_label_list_ptr[0] = NULL;
	prog_list->arg_label_list_ptr[1] = NULL;
	prog_list->arg_label_list_ptr[2] = NULL;
	prog_list->args_code[0] = 0;
	prog_list->args_code[1] = 0;
	prog_list->args_code[2] = 0;
}

int			ft_parse_new_line(t_prog_list *prog_list)
{
	size_t	i;

	ft_parse_new_line_prog_list_init(prog_list);
	i = 0;
	while ((prog_list->new_line)[i] != '\0')
	{
		if (!prog_list->command)
		{
			if (ft_parse_new_line_if(prog_list, &i))
				return (1);
		}
		else
		{
			if (ft_parse_new_line_else(prog_list, &i))
				return (1);
		}
	}
	return (0);
}
