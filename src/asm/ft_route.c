/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_route.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 19:17:32 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/22 19:17:39 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_file_asm_or_dis(char *file)
{
	size_t		length;

	if (file)
	{
		length = ft_strlen(file);
		if (file[length - 1] == 's' && file[length - 2] == '.' &&
			file[length - 3] != '/' && length > 3)
			return (1);
		else if (file[length - 1] == 'r' && file[length - 2] == 'o' &&
				 file[length - 3] == 'c' && file[length - 4] == '.' &&
				 file[length - 5] != '/' && length > 5)
			return (-1);
	}
	return (0);
}

static int	ft_get_opt(char *opt)
{
	if (opt)
	{
		if (!ft_strcmp(opt, "-asm"))
			return (1);
//		else if (!ft_strcmp(opt, "-aout"))
//			return (2);
		else if (!ft_strcmp(opt, "-dis"))
			return (-1);
		else if (!ft_strcmp(opt, "-dout"))
			return (-2);
	}
	return (0);
}

void		ft_dis_route(t_project *project)
{
	if (project->option >= -1)
	{
		if (ft_open_file_for_write(project))
			ft_exit(project, 3, NULL);
	}
	else if (project->option == -2)
	{
		project->fd = STDOUT_FILENO;
		ft_print_memory(
				project->name, project->end,
				project->comment, project->program);
		ft_set_color(white + 2);
	}
	ft_printf_fd(project->fd, ".name \"%s\"\n", project->name);
	ft_printf_fd(project->fd, ".comment \"%s\"\n\n", project->comment);
	project->current = project->program;
	while (project->current < project->end)
		ft_disassemble(project);
	if (project->option >= -1)
	{
		close(project->fd);
		ft_printf("Writing output program to %s\n", project->new_file);
		ft_exit(project, 0, NULL);
	}
}

void		ft_dis_asm_route(t_project *project, char *arg1, char *arg2)
{
	if (arg1 && !ft_get_opt(arg1))
		ft_usage();
	project->option = ft_get_opt(arg1);
	project->route = ft_file_asm_or_dis(arg2);
	project->file_name = arg2;
	if (project->option >= 0 && project->route > 0)
	{
		if (ft_project_init(project, ft_parse_file))
			ft_exit(project, 3, NULL);
	}
	else if (project->option <= 0 && project->route < 0)
	{
		if (ft_project_init(project, ft_parse_file_dis))
			ft_exit(project, 3, NULL);
		ft_dis_route(project);
	}
	else
		ft_usage();
}
