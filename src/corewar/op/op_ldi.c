#include "corewar.h"

t_err op_ldi(t_game* game)
{
	union u_types type;
	t_cursor *cursor;
	int arg1;
	int arg2;
	int arg3;
	size_t address;
	cursor = game->cursor;
	cursor->current = ft_mod(cursor->pc + OP_LEN, MEM_SIZE);
	type.value = ft_atoi_vm(game->arena, &cursor->current, TYPE_LEN).v_1;
	arg1 = ft_get_arg(game, type.arg1, true);
	arg2 = ft_get_arg(game, type.arg2, true);
	arg3 = ft_get_data(game, type.arg3);
	address = cursor->pc + (arg2 + arg1) % IDX_MOD;
	cursor->regs[arg3 - 1] = ft_atoi_vm(game->arena, &address, REG_SIZE).v_4;
	cursor->carry = cursor->regs[arg3 - 1]  ? false : true;
	return (success);
}