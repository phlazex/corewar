#include "corewar_op.h"
#include "ft_printf.h"
#include "asm.h"
#include "corewar.h"

int32_t ft_get_code(char *head, size_t *address, int op, int arg_type)
{
	int arg;
	arg = 0;
	if (arg_type == DIR_CODE)
	{
		if (g_op_tab[op].dir_size == 2)
			arg = ft_atoi_vm(head, address,
							 g_op_tab[op].dir_size).v_2;
		else
			arg = ft_atoi_vm(head, address,
							 g_op_tab[op].dir_size).v_4;
	}
	if (arg_type == IND_CODE)
		arg = ft_atoi_vm(head, address, IND_SIZE).v_2;
	if (arg_type == REG_CODE)
		arg = ft_atoi_vm(head, address, REG_LEN).v_1;
	return arg;
}

//static int ft_printf_arg(t_project *project, int32_t type_arg, int32_t op)
//{
//		type_arg == REG_CODE ? ft_printf("r") : ft_printf("%%");
//		ft_printf("%d", ft_get_code(project->program, &project->current, op, type_arg));
//}

int ft_disassemble(t_project *project)
{
	int op;
	union u_types type;
	size_t current;
	int32_t arg;

	op = *project->current - 1;
	if (op >= 0 && op < 16)
	{
		ft_printf("%s ", g_op_tab[op].name);

	current = OP_LEN;
	if (g_op_tab[op].arg_type)
	{
		type.value = ft_atoi_vm(project->current, &current, TYPE_LEN).v_1;
		type.args.arg1 == REG_CODE ? ft_printf("r") : ft_printf("%%");
		ft_printf("%d", ft_get_code(project->current, &current, op, type.args.arg1));
		if (g_op_tab[op].arg_count > 1)
		{
			type.args.arg2 == REG_CODE ? ft_printf(", r") : ft_printf(", %%");
			ft_printf("%d", ft_get_code(project->current, &current, op, type.args.arg2));
		}
		if (g_op_tab[op].arg_count > 2)
		{
			type.args.arg3 == REG_CODE ? ft_printf(", r") : ft_printf(", %%");
			ft_printf(", %d", ft_get_code(project->current, &current, op, type.args.arg3));
		}
		ft_printf("\n");
	} else
	{
		arg = ft_get_code(project->current, &current, op, DIR_CODE);
		ft_printf("%%%d\n", arg);
	}
		project->current += current;
		return 1;
	}
	ft_printf("err\n");
	project->current++;
	return 0;
}