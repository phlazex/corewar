
#include <fcntl.h>
#include <zconf.h>
#include "asm.h"
#include "libft.h"
#include "corewar.h"
#include "corewar_op.h"
#include <ft_printf.h>
#include <stdio.h>

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
//	ft_printf("%zi|", project->current);
	if ((!comment && project->current == project->data->endl) || (comment && comment == project->current))
	{
//		ft_printf("END|");
		return (1);
	}
	return (0);
}

static int	ft_is_labels_char(int chr, size_t length)
{
	size_t	i;

	i = 0;
	length = length ? length : ft_strlen(LABEL_CHARS);
//	ft_printf("|%zi|", length);
	while (LABEL_CHARS[i] != '\0' && i < length)
	{
		if (LABEL_CHARS[i] == chr)
		{
//			ft_printf("%c|", LABEL_CHARS[i]);
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
//		ft_printf("%c|", chr);
		return (1);
	}
	return (ft_is_labels_char(chr, 0));
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
//		ft_printf("ERROR|");
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
//		ft_printf("|%s|", ft_strsub(prog_list->new_line, i - j, j - 1));
		str = ft_strsub(prog_list->new_line, i - j, j - 1);
		if (ft_is_label_command(str, 0))
		{
			return (str);
		}
	}
	else if (ft_isalpha((prog_list->new_line)[i - 1]))
	{
//		ft_printf("|%s|", ft_strsub(prog_list->new_line, i - j, j));
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

//	ft_printf("\n|%s|%zi|%zi|", prog_list->new_line + i - 1, i, j);
	if (!prog_list->command)
	{
		if (!(word = ft_validation_label_name(prog_list, i, j)))
		{
//			ft_printf("ERROR|");
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
//			ft_printf("ERROR|");
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
//			ft_printf("|ERROR|");
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
	prog_list->arg_label_list_ptr[0] = NULL;
	prog_list->arg_label_list_ptr[1] = NULL;
	prog_list->arg_label_list_ptr[2] = NULL;
	prog_list->args_code[0] = 0;
	prog_list->args_code[1] = 0;
	prog_list->args_code[2] = 0;
	i = 0;
	while ((prog_list->new_line)[i] != '\0')
	{
//		ft_printf("|HELLO|");
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
//	ft_printf("\n|%s|", prog_list->new_line);
}

static t_prog_list	*ft_init_prog_list(t_project *project, char *comment)
{
	t_prog_list	*prog_list;

//	ft_printf("YES|");
	prog_list = (t_prog_list*)malloc(sizeof(t_prog_list));
	prog_list->line_ptr = project->data->current;
	prog_list->endl_ptr = comment ? comment : project->data->endl;
	ft_get_new_line(prog_list);
	ft_parse_new_line(prog_list);
	prog_list->prev_list = project->current_list;
	prog_list->next_list = NULL;
//	ft_printf("\n\t%zi|%zi|%zi|", prog_list, project->data->current, project->current_list);
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
//			ft_printf("NONAME|");
			if ((data_cmd = ft_get_str(project, NAME_CMD_STRING)) && (!comment || data_cmd < comment))
			{
				ft_get_name_comment(project, data_cmd, comment, NAME_CMD_STRING);
//				ft_printf("%zi{NAME_CMD}|", data_cmd);
			}
			else if ((data_cmd = ft_get_str(project, COMMENT_CMD_STRING)) && (!comment || data_cmd < comment))
			{
				ft_get_name_comment(project, data_cmd, comment, COMMENT_CMD_STRING);
//				ft_printf("%zi{COMMENT_CMD}|", data_cmd);
			}
			else
			{
				project->current = project->data->current;
				if (!ft_is_zero_line(project, comment))
				{
//					ft_printf("ERROR|");
				}
			}
		}
		else
		{
//			ft_printf("HERE|");
			if (!project->program)
			{
				project->program = project->data->current;
			}
			project->current = project->data->current;
			if (!ft_is_zero_line(project, comment))
			{
				if (!ft_is_valid_line(project, comment))
				{
//					ft_printf("ERROR|");
				}
				else if (!project->prog_list)
				{
					if (!(project->prog_list = ft_init_prog_list(project, comment)))
					{
//						ft_printf("ERROR|");
					}
					project->current_list = project->prog_list;
				}
				else if (project->prog_list)
				{
					if (!(project->current_list->next_list = ft_init_prog_list(project, comment)))
					{
//						ft_printf("ERROR|");
					}
					project->current_list = project->current_list->next_list;
				}
			}
		}
	}
}

static size_t	ft_check_command_name(t_project *project)
{
	size_t	i;

	i = 0;
	while (i < MAX_OP)
	{
		if (!ft_strcmp(project->current_list->command, g_op_tab[i].name))
		{
//			ft_printf("\n|%s|%s|%zi|", g_op_tab[i].name, project->current_list->command, i);
			return (i + 1);
		}
		i++;
	}
	return (0);
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
//	ft_printf("|%zi|", g_op_tab[project->current_list->command_num].arg_count);
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
//				ft_printf("\n\t\t%s|%s|\n\t\t\t", prog_list->label, label);
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
//				ft_printf("|%c|", project->current_list->args[arg_num][i++]);
			}
		}
		if (ft_atoi(project->current_list->args[arg_num] + 1) > 0)
		{
//			ft_printf("T_REG|");
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
//				ft_printf("T_DIR|");
				project->current_list->command_size += g_op_tab[project->current_list->command_num].dir_size;
				project->current_list->args_code[arg_num] = DIR_CODE;
				return (1);
			}
		}
		else
		{
			if (project->current_list->args[arg_num][--i] == '-')
			{
//			ft_printf("|i=%zic=%c|", i, project->current_list->args[arg_num][i]);
				i++;
			}
			len = ft_strlen(project->current_list->args[arg_num]);
			while (i < len)
			{
				if (ft_isdigit(project->current_list->args[arg_num][i++]) < 0)
				{
					return (0);
//				ft_printf("|%c|", project->current_list->args[arg_num][i++]);
				}
			}
//			ft_printf("T_DIR|");
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
//	ft_printf("HERE|");
	if (project->current_list->args[arg_num][i++] == LABEL_CHAR)
	{
		if (ft_is_label_command(project->current_list->args[arg_num] + i, 0) && ft_is_valid_label(project, project->current_list->args[arg_num] + i, arg_num))
		{
//			ft_printf("T_IND|");
			project->current_list->command_size += IND_SIZE;
			project->current_list->args_code[arg_num] = IND_CODE;
			return (1);
		}
	}
	else
	{
		if (project->current_list->args[arg_num][--i] == '-')
		{
//			ft_printf("|i=%zic=%c|", i, project->current_list->args[arg_num][i]);
			i++;
		}
		len = ft_strlen(project->current_list->args[arg_num]);
		while (i < len)
		{
			if (ft_isdigit(project->current_list->args[arg_num][i++]) < 0)
			{
				return (0);
//				ft_printf("|%c|", project->current_list->args[arg_num][i++]);
			}
		}
//		ft_printf("T_IND|");
		project->current_list->command_size += IND_SIZE;
		project->current_list->args_code[arg_num] = IND_CODE;
		return (1);
	}
	return (0);
}

static int 	ft_check_arg(t_project *project, size_t arg_num)
{
	size_t	size_type;

//	ft_printf("HERE|");
//	ft_printf("%zi|", g_op_tab[project->current_list->command_num].types[arg_num]);
	if ((size_type = g_op_tab[project->current_list->command_num].types[arg_num]) == 1)
	{
		if (!ft_is_reg(project, arg_num))
		{
			return (0);
		}
//		ft_printf("T_REG|");
	}
	else if (size_type == 2)
	{
		if (!ft_is_dir(project, arg_num))
		{
			return (0);
		}
//		ft_printf("T_DIR|");
	}
	else if (size_type == 3)
	{
		if (!(ft_is_reg(project, arg_num) || ft_is_dir(project, arg_num)))
		{
			return (0);
		}
//		ft_printf("T_REG/T_DIR|");
	}
	else if (size_type == 5)
	{
		if (!(ft_is_reg(project, arg_num) || ft_is_ind(project, arg_num)))
		{
			return (0);
		}
//		ft_printf("T_REG/T_IND|");
	}
	else if (size_type == 6)
	{
		if (!(ft_is_dir(project, arg_num) || ft_is_ind(project, arg_num)))
		{
			return (0);
		}
//		ft_printf("T_DIR/T_IND|");
	}
	else if (size_type == 7)
	{
		if (!(ft_is_reg(project, arg_num) || ft_is_dir(project, arg_num) || ft_is_ind(project, arg_num)))
		{
			return (0);
		}
//		ft_printf("T_REG/T_DIR/T_IND|");
	}
//	ft_printf("%zi|%zi|", project->current_list->command_size, project->current_list->args_code[arg_num]);
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
	size_t	cmd_num;

	if (project->current_list->command)
	{
		if (!(cmd_num = ft_check_command_name(project)))
		{
			return (0);
		}
		project->current_list->command_num = --cmd_num;
		project->current_list->command_size = 1 + g_op_tab[project->current_list->command_num].arg_type;
//		ft_printf("%zi|", project->current_list->command_num);
		if (!(ft_check_count_args(project) && ft_check_args(project)))
		{
			return (0);
		}
	}
	return (1);
}

static void ft_get_four_bytes(t_project *project, size_t *i, int num)
{
//	ft_printf("%x|", ((num >> 24) & 0xff));
//	ft_printf("%x|", ((num >> 16) & 0xff));
//	ft_printf("%x|", ((num >> 8) & 0xff));
//	ft_printf("%x|", ((num) & 0xff));
	project->current_list->code_line[(*i)++] = (num >> 24) & 0xff;
	project->current_list->code_line[(*i)++] = (num >> 16) & 0xff;
	project->current_list->code_line[(*i)++] = (num >> 8) & 0xff;
	project->current_list->code_line[(*i)++] = num & 0xff;
}

static void ft_get_two_bytes(t_project *project, size_t *i, int num)
{
//	ft_printf("%x|", ((num >> 8) & 0xff));
//	ft_printf("%x|", ((num) & 0xff));
//	ft_printf("HERE");
	project->current_list->code_line[(*i)++] = (num >> 8) & 0xff;
	project->current_list->code_line[(*i)++] = num & 0xff;
	ft_printf("%zi|%zi|", project->current_list->code_line[(*i) - 2], project->current_list->code_line[(*i) - 1]);
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
	return (num);
}

static int ft_get_num_label(t_project *project, size_t arg_num)
{
	int	num;

	num = 0;
	if (project->current_list->arg_label_list_ptr[arg_num] < project->current_list)
	{
		num = ~(ft_get_prev_num_label(project, arg_num)) + 1;
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
//		ft_printf("LABEL|");
		num = ft_get_num_label(project, arg_num);
	}
	else
	{
//		ft_printf("NOLABEL|");
		num = ft_atoi(project->current_list->args[arg_num] + 1);
	}
	if (g_op_tab[project->current_list->command_num].dir_size == DIR_SIZE)
	{
		ft_get_four_bytes(project, i, num);
	}
	else if (g_op_tab[project->current_list->command_num].dir_size == IND_SIZE)
	{
		ft_get_two_bytes(project, i, num);
	}
}

static void ft_get_arg_ind(t_project *project, size_t *i, size_t arg_num)
{
	int		num;

	if (project->current_list->arg_label_list_ptr[arg_num])
	{
//		ft_printf("LABEL|");
		num = ft_get_num_label(project, arg_num);
	}
	else
	{
//		ft_printf("NOLABEL|");
		num = ft_atoi(project->current_list->args[arg_num]);
	}
	ft_get_two_bytes(project, i, num);
}

static void ft_get_args(t_project *project, size_t *i)
{
	size_t	j;

	j = 0;
	while (j < g_op_tab[project->current_list->command_num].arg_count)
	{
//		ft_printf("%zi|", project->current_list->args_code[j]);
		if (project->current_list->args_code[j] == REG_CODE)
		{
			project->current_list->code_line[(*i)++] = ft_atoi(project->current_list->args[j] + 1);
//			ft_printf("atoi=%zi|", ft_atoi(project->current_list->args[j] + 1));
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
//		i++;
	}
//	ft_printf("%zi|", *i);
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
//	ft_printf("%x|", project->current_list->code_line[0]);
	if (g_op_tab[project->current_list->command_num].arg_type)
	{
		project->current_list->code_line[i++] = (project->current_list->args_code[0] << 6) + (project->current_list->args_code[1] << 4) + (project->current_list->args_code[2] << 2);
//		ft_printf("%x|", project->current_list->code_line[i - 1]);
	}
//	ft_printf("i=%zi|", i);
	ft_get_args(project, &i);
//	ft_printf("i=%zi|", i);
//	ft_printf("%x|", project->current_list->code_line[i - 1]);
	project->current_list->code_line[i] = 0;
	size_t k = 0;
	while (k < project->current_list->command_size)
	{
		ft_printf("%02x ", project->current_list->code_line[k++]);
	}
	ft_printf("\n");
	return (1);
}

static int 	ft_check_prog_list(t_project *project)
{
	project->current_list = project->prog_list;
	while (project->current_list)
	{
//		ft_printf("\n%zi|%zi|%zi|%zi|%zi|", ptr, ptr->prev_list, ptr->next_list, ptr->line_ptr, ptr->endl_ptr);
//		ft_printf("\n%s|\n\t%s|%s|%s|%s|%s|", project->current_list->new_line ? project->current_list->new_line : "(null)", project->current_list->label ? project->current_list->label : "(null)", project->current_list->command ? project->current_list->command : "(null)", project->current_list->args[0] ? project->current_list->args[0] : "(null)", project->current_list->args[1] ? project->current_list->args[1] : "(null)", project->current_list->args[2] ? project->current_list->args[2] : "(null)");
//		ft_printf("\n|");
//		tmp = ptr->line_ptr;
//		while (tmp < ptr->endl_ptr)
//		{
//			ft_printf("%c", *tmp);
//			tmp++;
//		}
//		ft_printf("|%s|", ptr->new_line);
		if (!ft_check_prog_list_line(project))
		{
			return (0);
		}
		project->prog_size += project->current_list->command_size;
		if (!ft_get_code_line(project))
		{
			return (0);
		}
		project->current_list = project->current_list->next_list;
	}
	return (1);
}

static int	ft_parse_file(t_mem *mem, t_project *project)
{
	project->data = mem;
	project->current = mem->head;
	project->end = mem->end;
	project->prog_size = 0;
	if ((mem->endl = ft_strchr(mem->head, '\n')))
	{
		mem->current = mem->head;
		while (mem->current < mem->end)
		{
			if ((mem->endl = ft_strchr(mem->current, '\n')))
			{
//				ft_printf("\n%zi|%zi|%zi|%zi|", mem->head, mem->current, mem->endl, mem->end);
				ft_parse_current(project);
				mem->current = mem->endl + 1;
			}
			else if ((mem->endl = ft_strchr(mem->current, '\0')))
			{
//				ft_printf("\n%zi|%zi|%zi|%zi|", mem->head, mem->current, mem->endl, mem->end);
				ft_parse_current(project);
				mem->current = mem->end;
			}
		}
//		ft_printf("\n%zi|%zi|%zi|%zi|", mem->head, mem->current, mem->endl, mem->end);
	}
	if ((!project->name || ft_strlen(project->name) > PROG_NAME_LENGTH) && (project->comment && ft_strlen(project->comment) > COMMENT_LENGTH))
	{
		ft_printf("ERROR|");
	}
	else
	{
//		size_t	x;
//		size_t	i;
//		size_t	j;
//		size_t	length;
//
//		x = COREWAR_EXEC_MAGIC;
//		length = sizeof(COREWAR_EXEC_MAGIC);
//		i = length;
//		project->program = ft_strnew((size_t)(i + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4 + project->prog_size));
//		while (x != 0)
//		{
////			ft_printf("%x", x & 0xff);
//			project->program[--length] = x & 0xff;
//			ft_printf("\n%c|%zi|", project->program[length], length);
//			x >>= 8;
//		}
//		j = 0;
//		length = ft_strlen(project->name);
//		while (j < PROG_NAME_LENGTH + 8)
//		{
//			if (j < length)
//			{
//				project->program[i++] = project->name[j++];
//			}
//			else
//			{
//				project->program[i++] = 0;
//			}
//		}
//		j = 0;
//		length = ft_strlen(project->comment);
//		while (j < (size_t)(COMMENT_LENGTH + 4 + project->prog_size))
//		{
//			if (j < length)
//			{
//				project->program[i++] = project->comment[j++];
//			}
//			else
//			{
//				project->program[i++] = 0;
//			}
//		}
//		project->program[i] = 0;
	}
//	ft_printf("%zi|", sizeof(COREWAR_EXEC_MAGIC));
//	ft_printf("%x|", ((COREWAR_EXEC_MAGIC >> 16) & 0xff));
//	ft_printf("%x|", ((COREWAR_EXEC_MAGIC >> 8) & 0xff));
//	ft_printf("%x|", ((COREWAR_EXEC_MAGIC) & 0xff));
	if (!ft_check_prog_list(project))
	{
		ft_printf("ERROR|");
	}
	ft_printf("%zi|%zi|", sizeof(int) * 4 + COMMENT_LENGTH + PROG_NAME_LENGTH + 1, project->prog_size);
//	ft_printf("\n|%s|%s|%s|", project->name, project->comment, project->program);
//	project->prog_size =  project->name + PROG_NAME_LENGTH + 4;
//	project->program = project->comment + COMMENT_LENGTH + 4;
//	ft_printf("\n%c|", project->program[3]);
//	ft_printf("%zi|", project->program);
//	size_t i = 0;
//	while (i < (size_t)(4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4 + project->prog_size))
//	{
//		ft_printf("%c", project->program[i]);
//		i++;
//	}
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