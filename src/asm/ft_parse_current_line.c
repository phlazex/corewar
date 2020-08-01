/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_current_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:56:33 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/30 13:58:45 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_parse_current_else(t_project *project, char *comment)
{
	project->current = project->data->current;
	if (!ft_is_zero_line(project, comment))
	{
		if (!ft_is_valid_line(project, comment))
		{
			project->num_error_line = project->num_current_line;
			ft_exit(project, 7, NULL);
		}
		else if (!project->prog_list)
		{
			if (!(project->prog_list = ft_init_prog_list(project, comment)))
				ft_exit(project, 2, NULL);
			project->current_list = project->prog_list;
		}
		else if (project->prog_list)
		{
			if (!(project->current_list->next_list =
					ft_init_prog_list(project, comment)))
				ft_exit(project, 2, NULL);
			project->current_list = project->current_list->next_list;
		}
	}
}

static void	ft_parse_current_if_else(t_project *project, char *comment)
{
	project->current = project->data->current;
	if (!ft_is_zero_line(project, comment))
	{
		project->num_error_line = project->num_current_line;
		if (!project->name && !project->comment)
			ft_exit(project, 6, NULL);
		else if (!project->name)
			ft_exit(project, 4, NAME_CMD_STRING);
		else if (!project->comment)
			ft_exit(project, 4, COMMENT_CMD_STRING);
		else
			ft_exit(project, 3, NULL);
	}
}

static void	ft_parse_current_if(
		t_project *project, char *comment, char *data_cmd)
{
	if ((data_cmd = ft_get_str(project, NAME_CMD_STRING)) &&
			(!comment || data_cmd < comment))
	{
		if (!ft_get_name_comment(project, data_cmd, comment, NAME_CMD_STRING))
			ft_exit(project, 3, NULL);
	}
	else if ((data_cmd = ft_get_str(project, COMMENT_CMD_STRING)) &&
			(!comment || data_cmd < comment))
	{
		if (!ft_get_name_comment(
				project, data_cmd, comment, COMMENT_CMD_STRING))
			ft_exit(project, 3, NULL);
	}
	else
		ft_parse_current_if_else(project, comment);
}

void		ft_parse_current(t_project *project)
{
	char	*comment;
	char	*alt_comment;
	char	*data_cmd;

	data_cmd = NULL;
	if (project->current <= project->data->current)
	{
		comment = ft_get_chr(project, COMMENT_CHAR);
		alt_comment = ft_get_chr(project, ALT_COMMENT_CHAR);
		if (comment && alt_comment)
			comment = comment < alt_comment ? comment : alt_comment;
		else if (!comment && alt_comment)
			comment = alt_comment;
		if (!project->name || !project->comment)
			ft_parse_current_if(project, comment, data_cmd);
		else
			ft_parse_current_else(project, comment);
	}
}
