//
// Created by xel on 13.03.2020.
//

#include <ft_printf.h>
#include "asm.h"
#include "corewar.h"

static int	ft_check_file(char *opt, char *file)
{
	char	*ptr;
	if (!ft_strcmp(opt, "-dis") && (ptr = ft_strstr(file, ".cor")))
	{
		if (*(ptr + 4) == 0)
		{
//			ft_printf("DIS=%c", *(ptr + 4));
			return (-1);
		}
	}
	else if (!ft_strcmp(opt, "-asm") && (ptr = ft_strstr(file, ".s")))
	{
		if (*(ptr + 2) == 0)
		{
//			ft_printf("ASM=%c", *(ptr + 2));
			return (1);
		}
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_project *project;
	int 		opt;

	ft_printf(CLR);
	if (argc == 3)
	{
		opt = 0;
		if ((opt = ft_check_file(argv[1], argv[2])) > 0 )
		{
			ft_project_init(argv[2], &project, ft_parse_file);
		}
		else if (opt < 0)
		{
			ft_project_init(argv[2], &project, ft_parse_file_dis);
			ft_print_memory(project->name, project->end, project->comment, project->program);
			ft_set_color(white + 2);
			ft_printf(".name \"%s\"\n", project->name);
			ft_printf(".comment \"%s\"\n\n", project->comment);
			project->current = project->program;
			while (project->current < project->end)
				ft_disassemble(project);
		}
		else
		{
			ft_usage();
		}
	}
	else
		ft_usage();
	return (0);
}