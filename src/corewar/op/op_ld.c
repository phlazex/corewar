#include "corewar.h"

size_t op_ld(t_game *game)
{
	union u_types type;
	t_cursor *cursor;
	int arg1;
	int arg2;
	cursor = game->cursor;
	cursor->current = (cursor->current + OP_LEN) % MEM_SIZE;
	type.value = ft_atoi_vm(game->arena, &cursor->current, TYPE_LEN).v_1;
	arg1 = ft_get_arg(game, type.arg1, true);
	arg2 = ft_get_data(game, type.arg2);
	cursor->regs[arg2 - 1] = arg1;
	cursor->carry = cursor->regs[arg2 - 1] ? false : true;
	return 0;
}