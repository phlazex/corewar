//
// Created by xel on 13.03.2020.
//

#include <ft_printf.h>
#include "asm.h"
#include "corewar.h"

static int	ft_check_file_name_asm(char *opt, char *file)
{
	char		*ptr;

	if (!ft_strcmp(opt, "-dis") && (ptr = ft_strstr(file, ".cor")))
	{
		if (*(ptr + 4) == 0)
			return (-1);
	}
	else if (!ft_strcmp(opt, "-asm") && (ptr = ft_strstr(file, ".s")))
	{
		if (*(ptr + 2) == 0)
			return (1);
	}
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
				project->name, project->end, project->comment, project->program
				);
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
	if (argc == 3)
	{
		ft_dis_asm_route(project, argv[1], argv[2]);
	}
	else if (argc == 2)
	{
		ft_dis_asm_route(project, "-asm", argv[1]);
	}
	else
		ft_usage();
	return (0);
}