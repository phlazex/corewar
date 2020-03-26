
#include <fcntl.h>
#include <zconf.h>
#include "asm.h"
#include "libft.h"
#include "corewar.h"

static int ft_parse_file(t_mem *mem, t_project *project)
{
	project->data = mem;
	project->name = mem->head + 4;
	project->prog_size =  project->name + PROG_NAME_LENGTH + 4;
	project->comment = project->prog_size + 4;
	project->program = project->comment + COMMENT_LENGTH + 4;
	project->end = mem->end;
	return 0;
}

int ft_project_init(char *file_name, t_project **project)
{
	int fd;
	t_mem *data;

	fd = open(file_name, O_RDONLY);
	if(!(*project = (t_project*)malloc(sizeof(**project))))
		return (1);
	data = ft_init_memory();
	fast_read_in_memory(fd, data);
	close(fd);
	ft_parse_file(data, *project);
	return 0;
}