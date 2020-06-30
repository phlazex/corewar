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

void	ft_parse_current(t_project *project)
{
	char	*comment;
	char	*alt_comment;
	char	*data_cmd;

	data_cmd = NULL;
	if (project->current <= project->data->current)
	{
//		ft_printf("%zi|%zi|", project->data->current, project->current);
		comment = ft_get_chr(project, COMMENT_CHAR);
		alt_comment = ft_get_chr(project, ALT_COMMENT_CHAR);
//		ft_printf("%zi{COMMENT}|%zi{ALT_COMMENT}|", comment, alt_comment);
		if (comment && alt_comment)
		{
			comment = comment < alt_comment ? comment : alt_comment;
		}
		else if (!comment && alt_comment)
		{
			comment = alt_comment;
		}
//		if (((comment = ft_get_chr(project, COMMENT_CHAR)) || (comment = ft_get_chr(project, ALT_COMMENT_CHAR))) && comment > project->data->current)
//		{
//			ft_printf("%zi{COMMENT}|", comment);
//		}
		if (!project->name || !project->comment)
		{
			if ((data_cmd = ft_get_str(project, NAME_CMD_STRING)) && (!comment || data_cmd < comment))
			{
				if (!ft_get_name_comment(project, data_cmd, comment, NAME_CMD_STRING))
				{
					ft_printf("ERROR11|"); //Не конец проверяемой строки
				}
			}
			else if ((data_cmd = ft_get_str(project, COMMENT_CMD_STRING)) && (!comment || data_cmd < comment))
			{
				if (!ft_get_name_comment(project, data_cmd, comment, COMMENT_CMD_STRING))
				{
//	ft_printf("%s|", project->current);
					ft_printf("ERROR12|"); //Не конец проверяемой строки
				}
			}
			else
			{
				project->current = project->data->current;
				if (!ft_is_zero_line(project, comment))
				{
//					ft_printf("\nERROR5|%zi|", project->num_current_line); //Не конец проверяемой строки
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
		}
		else
		{
			project->current = project->data->current;
			if (!ft_is_zero_line(project, comment))
			{
				if (!ft_is_valid_line(project, comment))
				{
					project->num_error_line = project->num_current_line;
					ft_exit(project, 7, NULL);
//					ft_printf("\nERROR6|%zi|", project->num_current_line); //Не конец проверяемой строки
				}
				else if (!project->prog_list)
				{
					if (!(project->prog_list = ft_init_prog_list(project, comment)))
					{
						ft_printf("ERROR7|"); //Ошибка памяти
					}
					project->current_list = project->prog_list;
				}
				else if (project->prog_list)
				{
					if (!(project->current_list->next_list = ft_init_prog_list(project, comment)))
					{
						ft_printf("ERROR8|");
					}
					project->current_list = project->current_list->next_list;
				}
			}
		}
	}
}
