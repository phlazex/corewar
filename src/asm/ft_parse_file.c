/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:43:49 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/30 13:44:42 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
//		ft_printf("\n%zi", project->current_list->num_line);
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

int	ft_parse_file(t_mem *mem, t_project *project, char *file)
{
	project->data = mem;
	project->current = mem->head;
	project->end = mem->end;
	project->size_program = 0;
	project->name = NULL;
	project->comment = NULL;
	project->program = NULL;
	project->prog_list = NULL;
	project->num_current_line = 0;
	project->num_error = 0;
	project->num_error_line = 0;
	if ((mem->endl = ft_strchr(mem->head, '\n')))
	{
		mem->current = mem->head;
		while (mem->current < mem->end)
		{
			project->num_current_line++;
//			ft_printf("\n%zi|", project->num_current_line);
//			ft_printf("%s|", mem->current);
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
	if ((!project->name || ft_strlen(project->name) > PROG_NAME_LENGTH) || (!project->comment || ft_strlen(project->comment) > COMMENT_LENGTH))
	{
		if (!project->name && !project->comment)
			ft_exit(project, 6, NULL);
		else if (ft_strlen(project->name) > PROG_NAME_LENGTH)
			ft_exit(project, 5, NAME_CMD_STRING);
		else if (ft_strlen(project->comment) > COMMENT_LENGTH)
			ft_exit(project, 5, COMMENT_CMD_STRING);
		else
			ft_exit(project, 3, NULL);
//		ft_printf("ERROR9|");
	}
	else
	{
		if (!ft_check_prog_list(project))
		{
			project->num_error_line = project->current_list->num_line;
			ft_exit(project, 7, NULL);
//			ft_printf("\nERROR10|%zi|", project->current_list->num_line);
		}
		ft_get_program_line(project);
	}
	ft_write_to_file(project, file);
	return (0);
}
