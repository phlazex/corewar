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


char  *ft_disassemble(char *program)
{
	int op;
	union u_types type;
	size_t current;
	int32_t arg;

	op = *program - 1;
	ft_printf("%s ", g_op_tab[op].name);
	current = OP_LEN;
	if (g_op_tab[op].arg_type)
	{
		type.value = ft_atoi_vm(program, &current, TYPE_LEN).v_1;
		type.arg1 == REG_CODE ? ft_printf("r") : ft_printf("%%");
		ft_printf("%d", ft_get_code(program, &current, op, type.arg1));
		if (g_op_tab[op].arg_count > 1)
		{
			type.arg2 == REG_CODE ? ft_printf(", r") : ft_printf(", %%");
			ft_printf("%d", ft_get_code(program, &current, op, type.arg2));
		}
		if (g_op_tab[op].arg_count > 2)
		{
			type.arg3 == REG_CODE ? ft_printf(", r") : ft_printf(", %%");
			ft_printf(", %d", ft_get_code(program, &current, op, type.arg3));
		}
		ft_printf("\n");
	}
	else
	{
		arg = ft_get_code(program, &current, op, DIR_CODE);
		ft_printf("%%%d\n", arg);
	}
	return program + current;
}