
#include <fcntl.h>
#include <zconf.h>
#include "asm.h"
#include "libft.h"
#include "corewar.h"
#include <ft_printf.h>

static char *ft_get_data_cmd(char *start, char *end)
{
	char	*newstr;

	if ((newstr = ft_strsub(start, 1, end - start - 1)))
		return (newstr);
	return (NULL);
}

static int	ft_isspace(int chr)
{
	return ((chr >= 9 && chr <= 13 || chr == 32));
}

static char	*ft_get_str(t_project *project, char *str)
{
	char *ptr;

	if ((ptr = ft_strstr(project->data->current, str)) && ptr < project->data->endl)
		return (ptr);
	return (NULL);
}

static char	*ft_get_chr(t_project *project, int chr)
{
	char *ptr;

	if ((ptr = ft_strchr(project->data->current, chr)) && ptr < project->data->endl)
		return (ptr);
	return (NULL);
}

static int	ft_get_name_comment(t_project *project, char *data_cmd, char *comment, char *cmd_name)
{
	char	*data_start;
	char	*data_end;

	project->current = project->data->current;
	while (project->current < data_cmd && ft_isspace(*(project->current)))
		(project->current)++;
	if (project->current == data_cmd)
		project->current += ft_strlen(cmd_name);
	if ((data_start = ft_strchr(project->current, '"')) && (data_end = ft_strchr(data_start + 1, '"')))
	{
		while (project->current < data_start && ft_isspace(*(project->current)))
			(project->current)++;
		if (project->current == data_start)
		{
			if ((!ft_strcmp(cmd_name, NAME_CMD_STRING) && (project->name = ft_get_data_cmd(data_start, data_end))) || (!ft_strcmp(cmd_name, COMMENT_CMD_STRING) && (project->comment = ft_get_data_cmd(data_start, data_end))))
				project->current = data_end + 1;
			data_end = comment ? comment : project->data->endl;
			while (project->current < data_end && ft_isspace(*(project->current)))
				(project->current)++;
			if (project->current == data_end)
				return (1);
		}
	}
	return (0);
}

static int	ft_is_zero_line(t_project *project, char *comment)
{
	while (project->current < project->data->endl && ft_isspace(*(project->current)))
	{
		(project->current)++;
	}
	ft_printf("%zi|", project->current);
	if ((!comment && project->current == project->data->endl) || (comment && comment == project->current))
	{
		ft_printf("END|");
		return (1);
	}
	return (0);
}

static int	ft_is_valid_chr(int chr)
{
	size_t	i;

	if (chr == '-' || chr == LABEL_CHAR || chr == DIRECT_CHAR || chr == SEPARATOR_CHAR || ft_isspace(chr))
	{
		ft_printf("%c|", chr);
		return (1);
	}
	else
	{
		i = 0;
		while (LABEL_CHARS[i] != '\0')
		{
			if (LABEL_CHARS[i] == chr)
			{
				ft_printf("%c|", LABEL_CHARS[i]);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

static int	ft_is_valid_line(t_project *project, char *comment)
{
	char	*end_line;

	end_line = comment ? comment : project->data->endl;
//	ft_printf("%s|", project->current);
	while (project->current < end_line && ft_is_valid_chr(*(project->current)))
	{
//		ft_printf("%c", *(project->current));
		(project->current)++;
	}
	if (project->current == end_line)
	{
		return (1);
	}
	return (0);
}

static size_t		ft_get_strlen(t_prog_list *prog_list)
{
	char *ptr;
	size_t	i;
	size_t	j;

	ptr = prog_list->line_ptr;
	i = 0;
	j = 0;
	while (ptr < prog_list->endl_ptr)
	{
		j++;
		while (ptr < prog_list->endl_ptr && ft_isspace(*(ptr)))
		{
			ptr++;
		}
		while (ptr < prog_list->endl_ptr && !ft_isspace(*(ptr)))
		{
			ptr++;
			i++;
		}
		while (ptr < prog_list->endl_ptr && ft_isspace(*(ptr)))
		{
			ptr++;
		}
	}
//	ft_printf("%zi|%zi|%zi|", i, j, i + j);
	return (i + j);
}

static void 		ft_get_new_line(t_prog_list *prog_list)
{
	char	*ptr;
	size_t	i;

//	ft_printf("%zi|", ft_get_strlen(prog_list));
	if (!(prog_list->new_line = ft_strnew(ft_get_strlen(prog_list))))
	{
		ft_printf("ERROR|");
	}
	ptr = prog_list->line_ptr;
	i = 0;
	while (ptr < prog_list->endl_ptr)
	{
		while (ptr < prog_list->endl_ptr && ft_isspace(*(ptr)))
		{
			ptr++;
		}
		while (ptr < prog_list->endl_ptr && !ft_isspace(*(ptr)))
		{
			(prog_list->new_line)[i++] = *ptr;
			ptr++;
		}
		while (ptr < prog_list->endl_ptr && ft_isspace(*(ptr)))
		{
			ptr++;
		}
		if (ptr < prog_list->endl_ptr)
		{
			(prog_list->new_line)[i++] = ' ';
		}
	}
	(prog_list->new_line)[i] = '\0';
}

static t_prog_list	*ft_init_prog_list(t_project *project, char *comment)
{
	t_prog_list	*prog_list;

	ft_printf("YES|");
	prog_list = (t_prog_list*)malloc(sizeof(t_prog_list));
	prog_list->line_ptr = project->data->current;
	prog_list->endl_ptr = comment ? comment : project->data->endl;
	ft_get_new_line(prog_list);
	prog_list->label = NULL;
	prog_list->command = NULL;
	prog_list->arg1 = NULL;
	prog_list->arg2 = NULL;
	prog_list->arg3 = NULL;
	prog_list->prev_list = project->current_list;
	prog_list->next_list = NULL;
	ft_printf("\n\t%zi|%zi|%zi|", prog_list, project->data->current, project->current_list);
	return (prog_list);
}

static void	ft_parse_current(t_project *project)
{
	char	*comment;
	char	*data_cmd;

	if (project->current <= project->data->current)
	{
		if (((comment = ft_get_chr(project, COMMENT_CHAR)) || (comment = ft_get_chr(project, ALT_COMMENT_CHAR))) && comment > project->data->current)
		{
			ft_printf("%zi{COMMENT}|", comment);
		}
		if (!project->name || !project->comment)
		{
//			ft_printf("NONAME|");
			if ((data_cmd = ft_get_str(project, NAME_CMD_STRING)) && (!comment || data_cmd < comment))
			{
				ft_get_name_comment(project, data_cmd, comment, NAME_CMD_STRING);
				ft_printf("%zi{NAME_CMD}|", data_cmd);
			}
			else if ((data_cmd = ft_get_str(project, COMMENT_CMD_STRING)) && (!comment || data_cmd < comment))
			{
				ft_get_name_comment(project, data_cmd, comment, COMMENT_CMD_STRING);
				ft_printf("%zi{COMMENT_CMD}|", data_cmd);
			}
			else
			{
				project->current = project->data->current;
				if (!ft_is_zero_line(project, comment))
				{
					ft_printf("ERROR|");
				}
			}
		}
		else
		{
			ft_printf("HERE|");
			if (!project->program)
			{
				project->program = project->data->current;
			}
			project->current = project->data->current;
			if (!ft_is_zero_line(project, comment))
			{
				if (!ft_is_valid_line(project, comment))
				{
					ft_printf("ERROR|");
				}
				else if (!project->prog_list)
				{
					if (!(project->prog_list = ft_init_prog_list(project, comment)))
					{
						ft_printf("ERROR|");
					}
					project->current_list = project->prog_list;
				}
				else if (project->prog_list)
				{
					if (!(project->current_list->next_list = ft_init_prog_list(project, comment)))
					{
						ft_printf("ERROR|");
					}
					project->current_list = project->current_list->next_list;
				}
			}
		}
	}
}

static int	ft_parse_file(t_mem *mem, t_project *project)
{
	project->data = mem;
	project->current = mem->head;
	project->end = mem->end;
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
//	ft_printf("\n|%s|%s|%s|", project->name, project->comment, project->program);
	t_prog_list	*ptr = project->prog_list;
	char *tmp;
	while (ptr)
	{
//		ft_printf("\n%zi|%zi|%zi|%zi|%zi|", ptr, ptr->prev_list, ptr->next_list, ptr->line_ptr, ptr->endl_ptr);
		ft_printf("\n|");
		tmp = ptr->line_ptr;
		while (tmp < ptr->endl_ptr)
		{
			ft_printf("%c", *tmp);
			tmp++;
		}
		ft_printf("|%s|", ptr->new_line);
		ptr = ptr->next_list;
	}
//	project->prog_size =  project->name + PROG_NAME_LENGTH + 4;
//	project->program = project->comment + COMMENT_LENGTH + 4;
	return (0);
}

int ft_project_init(char *file_name, t_project **project)
{
	int fd;
	t_mem *data;

	fd = open(file_name, O_RDONLY);
	if (!(*project = (t_project*)malloc(sizeof(**project))))
		return (1);
	data = ft_init_memory();
	fast_read_in_memory(fd, data);
	close(fd);
	ft_parse_file(data, *project);
	return (0);
}