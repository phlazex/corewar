
#include <fcntl.h>
#include <unistd.h>
#include "asm.h"
#include "libft.h"
#include "corewar.h"
#include "corewar_op.h"
#include <ft_printf.h>

static void	ft_free_mem(t_project *project)
{
	project->data->current = NULL;
	project->data->end = NULL;
	project->data->endl = NULL;
	ft_strdel(&(project->data->head));
	ft_memdel((void **)&(project->data));
}

static void	ft_free_prog_list()
{

}

static void	ft_free_project()
{

}

static void	ft_free(t_project *project)
{
	ft_free_mem(project);
	ft_free_prog_list();
	ft_free_project();
}

static void	ft_exit(t_project *project, int exit_code, char *message)
{
	ft_free(project);
	if (exit_code)
	{
		ft_printf("%s\n", message);
	}
	exit(exit_code);
}

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
	if ((!comment && project->current == project->data->endl) || (comment && comment == project->current))
	{
		return (1);
	}
	return (0);
}

static int	ft_is_labels_char(int chr, size_t length)
{
	size_t	i;

	i = 0;
	length = length ? length : ft_strlen(LABEL_CHARS);
	while (LABEL_CHARS[i] != '\0' && i < length)
	{
		if (LABEL_CHARS[i] == chr)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static int	ft_is_valid_chr(int chr)
{
	if (chr == '-' || chr == LABEL_CHAR || chr == DIRECT_CHAR || chr == SEPARATOR_CHAR || ft_isspace(chr))
	{
		return (1);
	}
	return (ft_is_labels_char(chr, 0));
}

static int	ft_is_valid_line(t_project *project, char *comment)
{
	char	*end_line;

	end_line = comment ? comment : project->data->endl;
	while (project->current < end_line && ft_is_valid_chr(*(project->current)))
	{
		(project->current)++;
	}
	if (project->current == end_line)
	{
		return (1);
	}
	ft_printf("%s|", project->current);
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
	return (i + j);
}

static void 		ft_get_new_line(t_prog_list *prog_list)
{
	char	*ptr;
	size_t	i;

	if (!(prog_list->new_line = ft_strnew(ft_get_strlen(prog_list))))
	{
		ft_printf("ERROR1|");
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

static int 			ft_is_label_command(char *str, size_t length)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_is_labels_char(str[i], length))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

static char			*ft_validation_label_name(t_prog_list *prog_list, size_t i, size_t j)
{
	char 	*str;

	if ((prog_list->new_line)[i - 1] == LABEL_CHAR)
	{
		str = ft_strsub(prog_list->new_line, i - j, j - 1);
		if (ft_is_label_command(str, 0))
		{
			return (str);
		}
	}
	else if (ft_isalpha((prog_list->new_line)[i - 1]))
	{
		str = ft_strsub(prog_list->new_line, i - j, j);
		if (ft_is_label_command(str, 26))
		{
			return (str);
		}
	}
	return (NULL);
}

static void 		ft_get_new_word(t_prog_list *prog_list, size_t i, size_t j)
{
	char	*word;

	if (!prog_list->command)
	{
		if (!(word = ft_validation_label_name(prog_list, i, j)))
		{
			ft_printf("ERROR2|");
		}
		if ((prog_list->new_line)[i - 1] == LABEL_CHAR && !prog_list->label && word)
		{
			prog_list->label = word;
		}
		else if (!prog_list->command && word)
		{
			prog_list->command = word;
		}
		else
		{
			ft_printf("ERROR3|");
		}
	}
	else
	{
		if ((prog_list->new_line)[i - 1] == SEPARATOR_CHAR && (word = ft_strsub(prog_list->new_line, i - j, j - 1)))
		{
//			ft_printf("|%s|", ft_strsub(prog_list->new_line, i - j, j - 1));
		}
		else if ((word = ft_strsub(prog_list->new_line, i - j, j)))
		{
//			ft_printf("|%s|", ft_strsub(prog_list->new_line, i - j, j));
		}
		if (!prog_list->args[0])
		{
			prog_list->args[0] = word;
		}
		else if (!prog_list->args[1])
		{
			prog_list->args[1] = word;
		}
		else if (!prog_list->args[2])
		{
			prog_list->args[2] = word;
		}
		else if (prog_list->args[0] && prog_list->args[1] && prog_list->args[2])
		{
			ft_printf("ERROR4|");
		}
	}
}

static void			ft_parse_new_line(t_prog_list *prog_list)
{
	size_t	i;
	size_t	j;

	prog_list->label = NULL;
	prog_list->command = NULL;
	prog_list->args[0] = NULL;
	prog_list->args[1] = NULL;
	prog_list->args[2] = NULL;
	prog_list->command_size = 0;
	prog_list->command_num = 0;
	prog_list->arg_label_list_ptr[0] = NULL;
	prog_list->arg_label_list_ptr[1] = NULL;
	prog_list->arg_label_list_ptr[2] = NULL;
	prog_list->args_code[0] = 0;
	prog_list->args_code[1] = 0;
	prog_list->args_code[2] = 0;
	i = 0;
	while ((prog_list->new_line)[i] != '\0')
	{
		j = 0;
		while ((prog_list->new_line)[i] != '\0' && !ft_isspace((prog_list->new_line)[i]))
		{
			j++;
			i++;
			if (prog_list->command && (prog_list->new_line)[i - 1] == SEPARATOR_CHAR && !ft_isspace((prog_list->new_line)[i]))
			{
				break ;
			}
		}
		ft_get_new_word(prog_list, i, j);
		while ((prog_list->new_line)[i] != '\0' && ft_isspace((prog_list->new_line)[i]))
		{
			i++;
		}
	}
}

static t_prog_list	*ft_init_prog_list(t_project *project, char *comment)
{
	t_prog_list	*prog_list;

	prog_list = (t_prog_list*)malloc(sizeof(t_prog_list));
	prog_list->line_ptr = project->data->current;
	prog_list->endl_ptr = comment ? comment : project->data->endl;
	ft_get_new_line(prog_list);
	ft_parse_new_line(prog_list);
	prog_list->prev_list = project->current_list;
	prog_list->next_list = NULL;
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
//			ft_printf("%zi{COMMENT}|", comment);
		}
		if (!project->name || !project->comment)
		{
			if ((data_cmd = ft_get_str(project, NAME_CMD_STRING)) && (!comment || data_cmd < comment))
			{
				ft_get_name_comment(project, data_cmd, comment, NAME_CMD_STRING);
			}
			else if ((data_cmd = ft_get_str(project, COMMENT_CMD_STRING)) && (!comment || data_cmd < comment))
			{
				ft_get_name_comment(project, data_cmd, comment, COMMENT_CMD_STRING);
			}
			else
			{
				project->current = project->data->current;
				if (!ft_is_zero_line(project, comment))
				{
					ft_printf("ERROR5|");
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
					ft_printf("ERROR6|");
//					ft_exit(project, 6, "ERROR6");
				}
				else if (!project->prog_list)
				{
					if (!(project->prog_list = ft_init_prog_list(project, comment)))
					{
						ft_printf("ERROR7|");
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

static int	ft_check_command_name(t_project *project)
{
	size_t	i;

	i = 0;
	while (i < MAX_OP)
	{
		if (!ft_strcmp(project->current_list->command, g_op_tab[i].name))
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

static int 	ft_check_count_args(t_project *project)
{
	int	i;

	i = 0;
	if (project->current_list->args[0])
	{
		i++;
	}
	if (project->current_list->args[1])
	{
		i++;
	}
	if (project->current_list->args[2])
	{
		i++;
	}
	if (i == g_op_tab[project->current_list->command_num].arg_count)
	{
		return (1);
	}
	return (0);
}

static int 	ft_is_valid_label(t_project *project, char *label, size_t arg_num)
{
	t_prog_list	*prog_list;

	prog_list = project->prog_list;
	while (prog_list)
	{
		if (prog_list->label)
		{
			if (!ft_strcmp(prog_list->label, label) && !project->current_list->arg_label_list_ptr[arg_num])
			{
				project->current_list->arg_label_list_ptr[arg_num] = prog_list;
			}
			else if (!ft_strcmp(prog_list->label, label) && project->current_list->arg_label_list_ptr[arg_num])
			{
				return (0);
			}
		}
		prog_list = prog_list->next_list;
	}
	if (!project->current_list->arg_label_list_ptr[arg_num])
	{
		return (0);
	}
	return (1);
}

static int	ft_is_reg(t_project *project, size_t arg_num)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (project->current_list->args[arg_num][i++] == 'r' && (len = ft_strlen(project->current_list->args[arg_num])) <= 3)
	{
		while (i < len)
		{
			if (ft_isdigit(project->current_list->args[arg_num][i++]) < 0)
			{
				return (0);
			}
		}
		if (ft_atoi(project->current_list->args[arg_num] + 1) > 0)
		{
			project->current_list->command_size += 1;
			project->current_list->args_code[arg_num] = REG_CODE;
			return (1);
		}
	}
	return (0);
}

static int	ft_is_dir(t_project *project, size_t arg_num)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (project->current_list->args[arg_num][i++] == DIRECT_CHAR)
	{
		if (project->current_list->args[arg_num][i++] == LABEL_CHAR)
		{
			if (ft_is_label_command(project->current_list->args[arg_num] + i, 0) && ft_is_valid_label(project, project->current_list->args[arg_num] + i, arg_num))
			{
				project->current_list->command_size += g_op_tab[project->current_list->command_num].dir_size;
				project->current_list->args_code[arg_num] = DIR_CODE;
				return (1);
			}
		}
		else
		{
			if (project->current_list->args[arg_num][--i] == '-')
			{
				i++;
			}
			len = ft_strlen(project->current_list->args[arg_num]);
			while (i < len)
			{
				if (ft_isdigit(project->current_list->args[arg_num][i++]) < 0)
				{
					return (0);
				}
			}
			project->current_list->command_size += g_op_tab[project->current_list->command_num].dir_size;
			project->current_list->args_code[arg_num] = DIR_CODE;
			return (1);
		}
	}
	return (0);
}

static int	ft_is_ind(t_project *project, size_t arg_num)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (project->current_list->args[arg_num][i++] == LABEL_CHAR)
	{
		if (ft_is_label_command(project->current_list->args[arg_num] + i, 0) && ft_is_valid_label(project, project->current_list->args[arg_num] + i, arg_num))
		{
			project->current_list->command_size += IND_SIZE;
			project->current_list->args_code[arg_num] = IND_CODE;
			return (1);
		}
	}
	else
	{
		if (project->current_list->args[arg_num][--i] == '-')
		{
			i++;
		}
		len = ft_strlen(project->current_list->args[arg_num]);
		while (i < len)
		{
			if (ft_isdigit(project->current_list->args[arg_num][i++]) < 0)
			{
				return (0);
			}
		}
		project->current_list->command_size += IND_SIZE;
		project->current_list->args_code[arg_num] = IND_CODE;
		return (1);
	}
	return (0);
}

static int 	ft_check_arg(t_project *project, size_t arg_num)
{
	size_t	size_type;

	size_type = 0;
	if ((size_type = g_op_tab[project->current_list->command_num].types[arg_num]) == 1)
	{
		if (!ft_is_reg(project, arg_num))
		{
			return (0);
		}
	}
	else if (size_type == 2)
	{
		if (!ft_is_dir(project, arg_num))
		{
			return (0);
		}
	}
	else if (size_type == 3)
	{
		if (!(ft_is_reg(project, arg_num) || ft_is_dir(project, arg_num)))
		{
			return (0);
		}
	}
	else if (size_type == 5)
	{
		if (!(ft_is_reg(project, arg_num) || ft_is_ind(project, arg_num)))
		{
			return (0);
		}
	}
	else if (size_type == 6)
	{
		if (!(ft_is_dir(project, arg_num) || ft_is_ind(project, arg_num)))
		{
			return (0);
		}
	}
	else if (size_type == 7)
	{
		if (!(ft_is_reg(project, arg_num) || ft_is_dir(project, arg_num) || ft_is_ind(project, arg_num)))
		{
			return (0);
		}
	}
	return (1);
}

static int 	ft_check_args(t_project *project)
{
	size_t	i;

	i = 0;
	while (i < g_op_tab[project->current_list->command_num].arg_count)
	{
		if (!ft_check_arg(project, i))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

static int 	ft_check_prog_list_line(t_project *project)
{
	int	cmd_num;

	if (project->current_list->command)
	{
		cmd_num = 0;
		if ((cmd_num = ft_check_command_name(project)) < 0)
		{
			return (0);
		}
		project->current_list->command_num = cmd_num;
		project->current_list->command_size = 1 + g_op_tab[project->current_list->command_num].arg_type;
		if (!(ft_check_count_args(project) && ft_check_args(project)))
		{
			return (0);
		}
	}
	return (1);
}

static void ft_get_four_bytes(char *str, size_t *i, int num)
{
	str[(*i)++] = (num >> 24) & 0xff;
	str[(*i)++] = (num >> 16) & 0xff;
	str[(*i)++] = (num >> 8) & 0xff;
	str[(*i)++] = num & 0xff;
}

static void ft_get_two_bytes(char *str, size_t *i, int num)
{
	str[(*i)++] = (num >> 8) & 0xff;
	str[(*i)++] = num & 0xff;
}

static int ft_get_next_num_label(t_project *project, size_t arg_num)
{
	t_prog_list	*next_prog_list;
	int	num;

	num = 0;
	next_prog_list = project->current_list;
	while (next_prog_list)
	{
		if (next_prog_list == project->current_list->arg_label_list_ptr[arg_num])
		{
			break ;
		}
		num += next_prog_list->command_size;
		next_prog_list = next_prog_list->next_list;
	}
	return (num);
}

static int ft_get_prev_num_label(t_project *project, size_t arg_num)
{
	t_prog_list	*prev_prog_list;
	int	num;

	num = 0;
	prev_prog_list = project->current_list->prev_list;
	while (prev_prog_list)
	{
		num += prev_prog_list->command_size;
		if (prev_prog_list == project->current_list->arg_label_list_ptr[arg_num])
		{
			break ;
		}
		prev_prog_list = prev_prog_list->prev_list;
	}
	return (-num);
}

static int ft_get_num_label(t_project *project, size_t arg_num)
{
	int	num;

	num = 0;
	if (project->current_list->arg_label_list_ptr[arg_num] < project->current_list)
	{
		num = ft_get_prev_num_label(project, arg_num);
	}
	else
	{
		num = ft_get_next_num_label(project, arg_num);
	}
	return (num);
}

static void ft_get_arg_dir(t_project *project, size_t *i, size_t arg_num)
{
	int		num;

	if (project->current_list->arg_label_list_ptr[arg_num])
	{
		num = ft_get_num_label(project, arg_num);
	}
	else
	{
		num = ft_atoi(project->current_list->args[arg_num] + 1);
	}
	if (g_op_tab[project->current_list->command_num].dir_size == DIR_SIZE)
	{
		ft_get_four_bytes(project->current_list->code_line, i, num);
	}
	else if (g_op_tab[project->current_list->command_num].dir_size == IND_SIZE)
	{
		ft_get_two_bytes(project->current_list->code_line, i, num);
	}
}

static void ft_get_arg_ind(t_project *project, size_t *i, size_t arg_num)
{
	int		num;

	if (project->current_list->arg_label_list_ptr[arg_num])
	{
		num = ft_get_num_label(project, arg_num);
	}
	else
	{
		num = ft_atoi(project->current_list->args[arg_num]);
	}
	ft_get_two_bytes(project->current_list->code_line, i, num);
}

static void ft_get_args(t_project *project, size_t *i)
{
	size_t	j;

	j = 0;
	while (j < g_op_tab[project->current_list->command_num].arg_count)
	{
		if (project->current_list->args_code[j] == REG_CODE)
		{
			project->current_list->code_line[(*i)++] = ft_atoi(project->current_list->args[j] + 1);
		}
		else if (project->current_list->args_code[j] == DIR_CODE)
		{
			ft_get_arg_dir(project, i, j);
		}
		else if (project->current_list->args_code[j] == IND_CODE)
		{
			ft_get_arg_ind(project, i, j);
		}
		j++;
	}
}

static int ft_get_code_line(t_project *project)
{
	size_t	i;

	if (!(project->current_list->code_line = ft_strnew(project->current_list->command_size + 1)))
	{
		return (0);
	}
	i = 0;
	project->current_list->code_line[i++] = g_op_tab[project->current_list->command_num].id;
	if (g_op_tab[project->current_list->command_num].arg_type)
	{
		project->current_list->code_line[i++] = (project->current_list->args_code[0] << 6) + (project->current_list->args_code[1] << 4) + (project->current_list->args_code[2] << 2);
	}
	ft_get_args(project, &i);
	project->current_list->code_line[i] = 0;
	return (1);
}

static int 	ft_check_prog_list(t_project *project)
{
	project->current_list = project->prog_list;
	while (project->current_list)
	{
		if (!ft_check_prog_list_line(project))
		{
			return (0);
		}
		project->size_program += project->current_list->command_size;
		project->current_list = project->current_list->next_list;
	}
	return (1);
}

static int 	ft_get_program_line(t_project *project)
{
	size_t	i;
	size_t	length;

	length = (size_t)(sizeof(int) * 4 + COMMENT_LENGTH + PROG_NAME_LENGTH + project->size_program);
	project->program = ft_strnew(length + 1);
	project->program = ft_memset(project->program, 0, length + 1);
	i = 0;
	ft_get_four_bytes(project->program, &i, COREWAR_EXEC_MAGIC);
	ft_strncpy(project->program + i, project->name, PROG_NAME_LENGTH);
	i += PROG_NAME_LENGTH;
	ft_get_four_bytes(project->program, &i, 0);
	ft_get_four_bytes(project->program, &i, project->size_program);
	ft_strncpy(project->program + i, project->comment, COMMENT_LENGTH);
	i += COMMENT_LENGTH;
	ft_get_four_bytes(project->program, &i, 0);
	project->current_list = project->prog_list;
	while (project->current_list)
	{
		if (!ft_get_code_line(project))
		{
			return (0);
		}
		ft_memcpy(project->program + i, project->current_list->code_line, project->current_list->command_size);
		i += project->current_list->command_size;
		project->current_list = project->current_list->next_list;
	}
//	size_t	z = 0;
//	while (z < length)
//	{
//		ft_printf("%c", project->program[z++]);
//		ft_printf("%zi ", project->program[z++]);
//		ft_printf("%x ", project->program[z++]);
//	}
	return (1);
}

static char	*ft_get_file_name(char *file)
{
	char	*ptr;
	char 	*new_file;

	if ((ptr = ft_strstr(file, ".s")))
	{
		new_file = ft_strsub(file, 0, ptr - file);
		new_file = ft_strjoin_free_first(&new_file, ".cor_new");
		return (new_file);
	}
	return (NULL);
}

static int	ft_write_to_file(t_project *project, char *file)
{
	int		fd;
	size_t	length;
	char	*new_file;

	new_file = NULL;
	if ((new_file = ft_get_file_name(file)))
	{
		if ((fd = open(new_file, O_WRONLY | O_TRUNC | O_CREAT , 0666)) <= 0)
		{
			return (1);
		}
	}
	else
	{
		return (1);
	}
	length = (size_t)(sizeof(int) * 4 + COMMENT_LENGTH + PROG_NAME_LENGTH + project->size_program);
	write(fd, project->program, length);
	close(fd);
	ft_printf("Writing output program to %s\n", new_file);
	ft_strdel(&new_file);
	return (0);
}

int	ft_parse_file(t_mem *mem, t_project *project, char *file)
{
	project->data = mem;
	project->current = mem->head;
	project->end = mem->end;
	project->size_program = 0;
	project->name = NULL;
	project->comment = NULL;
	project->program = NULL;
	if ((mem->endl = ft_strchr(mem->head, '\n')))
	{
		mem->current = mem->head;
		while (mem->current < mem->end)
		{
			if ((mem->endl = ft_strchr(mem->current, '\n')))
			{
				ft_parse_current(project);
				mem->current = mem->endl + 1;
			}
			else if ((mem->endl = ft_strchr(mem->current, '\0')))
			{
				ft_parse_current(project);
				mem->current = mem->end;
			}
		}
	}
	if ((!project->name || ft_strlen(project->name) > PROG_NAME_LENGTH) && (project->comment && ft_strlen(project->comment) > COMMENT_LENGTH))
	{
		ft_printf("ERROR9|");
	}
	else
	{
		if (!ft_check_prog_list(project))
		{
			ft_printf("ERROR10|");
		}
		ft_get_program_line(project);
	}
	ft_write_to_file(project, file);
	return (0);
}

int ft_parse_file_dis(t_mem *mem, t_project *project, char *file)
{
	project->data = mem;
	project->name = mem->head + 4;
	project->prog_size =  project->name + PROG_NAME_LENGTH + 4;
	project->comment = project->prog_size + 4;
	project->program = project->comment + COMMENT_LENGTH + 4;
	project->end = mem->end;
	return (0);
}

int ft_project_init(char *file_name, t_project **project, int (*ft_parse)(t_mem *, t_project *, char *))
{
	int fd;
	t_mem *data;

	fd = open(file_name, O_RDONLY);
	if (!(*project = (t_project*)malloc(sizeof(**project))))
		return (1);
	data = ft_init_memory();
	fast_read_in_memory(fd, data);
	close(fd);
	(*ft_parse)(data, *project, file_name);
	return (0);
}