//
// Created by xel on 13.03.2020.
//

#include <ft_printf.h>
#include "asm.h"
#include "corewar.h"

int main(int argc, char **argv)
{
	t_project *project;

	ft_printf(CLR);
	if (argc == 2)
	{
		ft_project_init(argv[1], &project);
		ft_print_memory(project->name, project->end, project->comment, project->program);
		ft_set_color(white + 2);
		ft_printf(".name \"%s\"\n", project->name);
		ft_printf(".comment \"%s\"\n\n", project->comment);
		project->current = project->program;
		while (project->current < project->end)
			ft_disassemble(project);
	}
	else
		ft_usage();
	return (0);
}