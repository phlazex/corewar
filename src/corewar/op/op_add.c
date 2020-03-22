#include "corewar.h"

t_err op_add(t_game* game)
{
	union u_types type;
	t_cursor *cursor;
	int arg1;
	int arg2;
	int arg3;
	cursor = game->cursor;
	cursor->current = ft_mod(cursor->current + OP_LEN, MEM_SIZE);
	type.value = ft_atoi_vm(game->arena, &cursor->current, TYPE_LEN).v_1;
	arg1 = ft_get_data(game, type.arg1);
	arg2 = ft_get_data(game, type.arg2);
	arg3 = ft_get_data(game, type.arg3);
	cursor->regs[arg3 - 1] = cursor->regs[arg1 - 1] + cursor->regs[arg2 - 1];
	cursor->carry = cursor->regs[arg3 - 1] ? false : true;
	return (success);
}