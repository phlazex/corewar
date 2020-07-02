/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_prog_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:11:01 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/30 15:18:31 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static size_t	ft_get_strlen(t_prog_list *prog_list)
{
	char		*ptr;
	size_t		i;
	size_t		j;

	ptr = prog_list->line_ptr;
	i = 0;
	j = 0;
	while (ptr < prog_list->endl_ptr)
	{
		j++;
		while (ptr < prog_list->endl_ptr && ft_isspace(*(ptr)))
			ptr++;
		while (ptr < prog_list->endl_ptr && !ft_isspace(*(ptr)))
		{
			ptr++;
			i++;
		}
		while (ptr < prog_list->endl_ptr && ft_isspace(*(ptr)))
			ptr++;
	}
	return (i + j);
}

static int		ft_get_new_line(t_prog_list *prog_list)
{
	char		*ptr;
	size_t		i;

	if (!(prog_list->new_line = ft_strnew(ft_get_strlen(prog_list))))
		ft_exit(NULL, 2, NULL);
	ptr = prog_list->line_ptr;
	i = 0;
	while (ptr < prog_list->endl_ptr)
	{
		while (ptr < prog_list->endl_ptr && ft_isspace(*(ptr)))
			ptr++;
		while (ptr < prog_list->endl_ptr && !ft_isspace(*(ptr)))
		{
			(prog_list->new_line)[i++] = *ptr;
			ptr++;
		}
		while (ptr < prog_list->endl_ptr && ft_isspace(*(ptr)))
			ptr++;
		if (ptr < prog_list->endl_ptr)
			(prog_list->new_line)[i++] = ' ';
	}
	(prog_list->new_line)[i] = '\0';
	return (0);
}

t_prog_list		*ft_init_prog_list(t_project *project, char *comment)
{
	t_prog_list	*prog_list;

	if (!(prog_list = (t_prog_list*)malloc(sizeof(t_prog_list))))
		return (NULL);
	prog_list->num_line = project->num_current_line;
	prog_list->line_ptr = project->data->current;
	prog_list->endl_ptr = comment ? comment : project->data->endl;
	if (ft_get_new_line(prog_list) || ft_parse_new_line(prog_list))
		return (NULL);
	prog_list->prev_list = project->current_list;
	prog_list->next_list = NULL;
	return (prog_list);
}
