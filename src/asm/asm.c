/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 19:17:32 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/22 19:17:39 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*ft_get_opt(char *file)
{
	size_t		length;

	if (file)
	{
		length = ft_strlen(file);
		if (file[length - 1] == 's' && file[length - 2] == '.' && length > 3)
			return ("-asm");
		else if (file[length - 1] == 'r' && file[length - 2] == 'o' &&
				 file[length - 3] == 'c' && file[length - 4] == '.' &&
				 length > 5)
			return ("-dis");
	}
	return (NULL);
}

static int	ft_check_file_name_asm(char *opt, char *file)
{
	if (!opt)
		opt = ft_get_opt(file);
	if (!ft_strcmp(opt, "-dis") && !ft_strcmp(ft_get_opt(file), "-dis"))
		return (-1);
	else if (!ft_strcmp(opt, "-asm") && !ft_strcmp(ft_get_opt(file), "-asm"))
		return (1);
	return (0);
}

static void	ft_dis_asm_route(t_project *project, char *arg1, char *arg2)
{
	int			opt;

	opt = ft_check_file_name_asm(arg1, arg2);
	if (opt > 0)
	{
		if (ft_project_init(arg2, &project, ft_parse_file))
			ft_exit(project, 3, NULL);
	}
	else if (opt < 0)
	{
		if (ft_project_init(arg2, &project, ft_parse_file_dis))
			ft_exit(project, 3, NULL);
		ft_print_memory(
				project->name, project->end,
				project->comment, project->program);
		ft_set_color(white + 2);
		ft_printf(".name \"%s\"\n", project->name);
		ft_printf(".comment \"%s\"\n\n", project->comment);
		project->current = project->program;
		while (project->current < project->end)
			ft_disassemble(project);
	}
	else
		ft_usage();
}

int			main(int argc, char **argv)
{
	t_project	*project;

	ft_printf(CLR);
	if (argc == 2)
		ft_dis_asm_route(project, NULL, argv[1]);
	else if (argc == 3)
		ft_dis_asm_route(project, argv[1], argv[2]);
	else
		ft_usage();
	return (0);
}
