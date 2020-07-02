/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 14:11:31 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/30 14:13:18 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_is_labels_char(int chr, size_t length)
{
	size_t	i;

	i = 0;
	length = length ? length : ft_strlen(LABEL_CHARS);
	while (LABEL_CHARS[i] != '\0' && i < length)
	{
		if (LABEL_CHARS[i] == chr)
			return (1);
		i++;
	}
	return (0);
}

int			ft_is_label_command(char *str, size_t length)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_is_labels_char(str[i], length))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_is_valid_chr(int chr)
{
	if (chr == '-' || chr == LABEL_CHAR || chr == DIRECT_CHAR ||
			chr == SEPARATOR_CHAR || ft_isspace(chr))
		return (1);
	return (ft_is_labels_char(chr, 0));
}

int			ft_is_valid_line(t_project *project, char *comment)
{
	char	*end_line;

	end_line = comment ? comment : project->data->endl;
	while (project->current < end_line && ft_is_valid_chr(*(project->current)))
		(project->current)++;
	if (project->current == end_line)
		return (1);
	return (0);
}

int			ft_is_zero_line(t_project *project, char *comment)
{
	while (project->current < project->data->endl &&
			ft_isspace(*(project->current)))
		(project->current)++;
	if ((!comment && project->current == project->data->endl) ||
			(comment && comment == project->current))
		return (1);
	return (0);
}
