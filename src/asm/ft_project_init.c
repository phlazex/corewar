
#include <fcntl.h>
#include <zconf.h>
#include "asm.h"
#include "libft.h"
#include "corewar.h"
#include <ft_printf.h>

//static char *ft_name_comment(char *str)
//{
//	char	*start;
//	char	*end;
//	char	*newstr;
//
//	if ((start = ft_strchr(str, '"')) && (end = ft_strchr(start + 1, '"')))
//	{
//		newstr = ft_strsub(start, 1, end - start - 1);
//	}
//	return (newstr);
//}

static void	ft_parse_current(t_project *project)
{
	if (project->data->current == project->data->head)
	{
		ft_printf("START");
	}
	else
	{
		ft_printf("NEXT");
	}
}

static int	ft_parse_file(t_mem *mem, t_project *project)
{
	project->data = mem;
	if ((mem->endl = ft_strchr(mem->head, '\n')))
	{
		mem->current = mem->head;
//		ft_printf("%s|%zi", mem->end, mem->end);
	}
	while (mem->current < mem->end)
	{
		ft_parse_current(project);
//		ft_printf("%s|", project->name);
		if ((mem->endl = ft_strchr(mem->current, '\n')))
		{
			mem->current = mem->endl + 1;
		}
	}
//	if ((project->name = ft_strstr(mem->head, NAME_CMD_STRING)) && (project->comment = ft_strstr(mem->head, COMMENT_CMD_STRING)))
//	{
//		if (mem->head == project->name || mem->head == project->comment)
//		{
//			if (!ft_strstr(project->name + 1, NAME_CMD_STRING) && !ft_strstr(project->comment + 1, COMMENT_CMD_STRING))
//			{
//				project->name = ft_name_comment(project->name);
//				project->comment = ft_name_comment(project->comment);
//				ft_printf("%s|%s|%s", mem->head, project->name, project->comment);
//			}
//		}
//	}
//	project->name = mem->head + 4;
//	project->prog_size =  project->name + PROG_NAME_LENGTH + 4;
//	project->comment = project->prog_size + 4;
//	project->program = project->comment + COMMENT_LENGTH + 4;
//	project->end = mem->end;
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