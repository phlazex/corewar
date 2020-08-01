/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_disassemble.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 19:17:56 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/30 13:36:28 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int32_t	ft_get_code(char *head, size_t *address, int op, int arg_type)
{
	int				arg;

	arg = 0;
	if (arg_type == DIR_CODE)
	{
		if (g_op_tab[op].dir_size == 2)
			arg = ft_atoi_vm(head, address, g_op_tab[op].dir_size).v_2;
		else
			arg = ft_atoi_vm(head, address, g_op_tab[op].dir_size).v_4;
	}
	if (arg_type == IND_CODE)
		arg = ft_atoi_vm(head, address, IND_SIZE).v_2;
	if (arg_type == REG_CODE)
		arg = ft_atoi_vm(head, address, REG_LEN).v_1;
	return (arg);
}

static void		ft_disassemble_print_args(
		t_project *project, union u_types type, size_t *current, int op)
{
	if (g_op_tab[op].arg_count > 1)
	{
		if (type.args.arg2 == REG_CODE)
			ft_printf_fd(project->fd, ", r");
		else if (type.args.arg2 == DIR_CODE)
			ft_printf_fd(project->fd, ", %%");
		else if (type.args.arg2 == IND_CODE)
			ft_printf_fd(project->fd, ", ");
		ft_printf_fd(project->fd, "%d",
				ft_get_code(project->current, current, op, type.args.arg2));
	}
	if (g_op_tab[op].arg_count > 2)
	{
		if (type.args.arg3 == REG_CODE)
			ft_printf_fd(project->fd, ", r");
		else if (type.args.arg3 == DIR_CODE)
			ft_printf_fd(project->fd, ", %%");
		else if (type.args.arg3 == IND_CODE)
			ft_printf_fd(project->fd, ", ");
		ft_printf_fd(project->fd, "%d",
				ft_get_code(project->current, current, op, type.args.arg3));
	}
}

static int		ft_disassemble_if(t_project *project, int op)
{
	union u_types	type;
	size_t			current;
	int32_t			arg;

	ft_printf_fd(project->fd, "%s ", g_op_tab[op].name);
	current = OP_LEN;
	if (g_op_tab[op].arg_type)
	{
		type.value = ft_atoi_vm(project->current, &current, TYPE_LEN).v_1;
		if (type.args.arg1 == REG_CODE)
			ft_printf_fd(project->fd, "r");
		else if (type.args.arg1 == DIR_CODE)
			ft_printf_fd(project->fd, "%%");
		ft_printf_fd(project->fd, "%d",
				ft_get_code(project->current, &current, op, type.args.arg1));
		ft_disassemble_print_args(project, type, &current, op);
		ft_printf_fd(project->fd, "\n");
	}
	else
	{
		arg = ft_get_code(project->current, &current, op, DIR_CODE);
		ft_printf_fd(project->fd, "%%%d\n", arg);
	}
	project->current += current;
	return (1);
}

int				ft_disassemble(t_project *project)
{
	int				op;

	op = *project->current - 1;
	if (op >= 0 && op < 16)
		return (ft_disassemble_if(project, op));
	ft_printf_fd(project->fd, "err\n");
	project->current++;
	return (0);
}
