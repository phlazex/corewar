/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_current_line_getters.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 14:43:20 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/30 14:44:48 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*ft_get_data_cmd(char *start, char *end)
{
	char	*newstr;

	if ((newstr = ft_strsub(start, 1, end - start - 1)))
		return (newstr);
	return (NULL);
}

static int	ft_get_name_comment_if(
		t_project *project, char *comment, char *data_end)
{
	if (data_end < project->data->endl)
	{
		data_end = comment ? comment : project->data->endl;
		while (project->current < data_end && ft_isspace(*(project->current)))
			(project->current)++;
		if (project->current == data_end)
			return (1);
	}
	else
	{
		while (ft_isspace(*(project->current)) && *(project->current) !=
				'\n' && *(project->current) != '\0' && *(project->current) !=
				COMMENT_CHAR && *(project->current) != ALT_COMMENT_CHAR)
			(project->current)++;
		if (*(project->current) == '\n' || *(project->current) == '\0' ||
				*(project->current) == COMMENT_CHAR ||
				*(project->current) == ALT_COMMENT_CHAR)
			return (1);
	}
	return (0);
}

int			ft_get_name_comment(
		t_project *project, char *data_cmd, char *comment, char *cmd_name)
{
	char	*data_start;
	char	*data_end;

	project->current = project->data->current;
	while (project->current < data_cmd && ft_isspace(*(project->current)))
		(project->current)++;
	if (project->current == data_cmd)
		project->current += ft_strlen(cmd_name);
	if ((data_start = ft_strchr(project->current, '"')) &&
			(data_end = ft_strchr(data_start + 1, '"')))
	{
		while (project->current < data_start && ft_isspace(*(project->current)))
			(project->current)++;
		if (project->current == data_start)
		{
			if ((!ft_strcmp(cmd_name, NAME_CMD_STRING) && (project->name =
					ft_get_data_cmd(data_start, data_end))) ||
					(!ft_strcmp(cmd_name, COMMENT_CMD_STRING) &&
					(project->comment = ft_get_data_cmd(data_start, data_end))))
				project->current = data_end + 1;
			if (ft_get_name_comment_if(project, comment, data_end))
				return (1);
		}
	}
	return (0);
}

char		*ft_get_str(t_project *project, char *str)
{
	char	*ptr;

	if ((ptr = ft_strstr(project->data->current, str)) &&
			ptr < project->data->endl)
		return (ptr);
	return (NULL);
}

char		*ft_get_chr(t_project *project, int chr)
{
	char	*ptr;

	if ((ptr = ft_strchr(project->data->current, chr)) &&
			ptr < project->data->endl)
		return (ptr);
	return (NULL);
}
