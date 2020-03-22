#include "corewar.h"

t_err op_lld(t_game *game)
{
	union u_types type;
	t_cursor *cursor;
	int32_t arg1;
	int32_t arg2;

	cursor = game->cursor;
	cursor->current = ft_mod(cursor->current + OP_LEN, MEM_SIZE);
	type.value = ft_atoi_vm(game->arena, &cursor->current, TYPE_LEN).v_1;
	arg1 = ft_get_arg(game, type.arg1, false);
	arg2 = ft_get_data(game, type.arg2);
	cursor->regs[arg2 - 1] = arg1;
	cursor->carry = cursor->regs[arg2 - 1] ? false : true;
	return (success);
}