
#include <fcntl.h>
#include <zconf.h>
#include "asm.h"
#include "libft.h"
#include "corewar.h"
#include <ft_printf.h>
//#include <stdio.h>

static char	*ft_get_str(t_project *project, char *str)
{
	char *ptr;

	if ((ptr = ft_strstr(project->data->current, str)) && ptr < project->data->endl)
	{
//		ft_printf("STR|");
		return (ptr);
	}
//	ft_printf("NOSTR|");
	return (NULL);
}

static char	*ft_get_chr(t_project *project, int chr)
{
	char *ptr;

	if ((ptr = ft_strchr(project->data->current, chr)) && ptr < project->data->endl)
	{
//		ft_printf("CHAR|");
		return (ptr);
	}
//	ft_printf("NOCHAR|");
	return (NULL);
}

static void	ft_parse_current(t_project *project)
{
	char	*comment;
	char	*name_cmd;
	char	*comment_cmd;

	if (!project->name || !project->data)
	{
//		ft_printf("NONAME|");
		if (((comment = ft_get_chr(project, COMMENT_CHAR)) || (comment = ft_get_chr(project, ALT_COMMENT_CHAR))) && comment > project->data->current)
		{
			ft_printf("%zi{COMMENT}|", comment);
		}
		if ((name_cmd = ft_get_str(project, NAME_CMD_STRING)) && (!comment || name_cmd < comment))
		{
			ft_printf("%zi{NAME_CMD}|", name_cmd);
		}
		else if ((comment_cmd = ft_get_str(project, COMMENT_CMD_STRING)) && (!comment || comment_cmd < comment))
		{
			ft_printf("%zi{COMMENT_CMD}|", comment_cmd);
		}
	}
}

static char *ft_get_data_cmd(char *str)
{
	char	*start;
	char	*end;
	char	*newstr;

	if ((start = ft_strchr(str, '"')) && (end = ft_strchr(start + 1, '"')))
	{
		newstr = ft_strsub(start, 1, end - start - 1);
		return (newstr);
	}
	return (NULL);
}

static int	ft_get_name_comment(t_project *project)
{
	char *name;
	char *comment;

	if ((name = ft_strstr(project->data->head, NAME_CMD_STRING)) && (comment = ft_strstr(project->data->head, COMMENT_CMD_STRING)) && (!ft_strstr(name + 1, NAME_CMD_STRING) && !ft_strstr(comment + 1, COMMENT_CMD_STRING)) && ((project->name = ft_get_data_cmd(name)) && (project->comment = ft_get_data_cmd(comment))))
	{
		return (1);
	}
	return (0);
}

static int	ft_parse_file(t_mem *mem, t_project *project)
{
	project->data = mem;
	project->end = mem->end;
//	if (ft_get_name_comment(project))
//	{
//		ft_printf("%s|%s|%s", project->data->head, project->name, project->comment);
		if ((mem->endl = ft_strchr(mem->head, '\n')))
		{
			mem->current = mem->head;
			while (mem->current < mem->end)
			{
				if ((mem->endl = ft_strchr(mem->current, '\n')))
				{
					ft_printf("\n%zi|%zi|%zi|%zi|", mem->head, mem->current, mem->endl, mem->end);
					ft_parse_current(project);
					mem->current = mem->endl + 1;
				}
				else if ((mem->endl = ft_strchr(mem->current, '\0')))
				{
					ft_printf("\n%zi|%zi|%zi|%zi|", mem->head, mem->current, mem->endl, mem->end);
					ft_parse_current(project);
					mem->current = mem->end;
				}
			}
//		ft_printf("\n%zi|%zi|%zi|%zi|", mem->head, mem->current, mem->endl, mem->end);
		}
//	}
//	project->prog_size =  project->name + PROG_NAME_LENGTH + 4;
//	project->program = project->comment + COMMENT_LENGTH + 4;
	return (0);
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
	return (0);
}