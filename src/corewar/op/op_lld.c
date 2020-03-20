#include "corewar.h"

size_t op_lld(t_game *game)
{
	union u_types type;
	t_cursor *cursor;
	int arg1;
	int arg2;
	cursor = (t_cursor*)game->cursor->content;
	cursor->current = (cursor->current + OP_LEN) % MEM_SIZE;
	type.value = ft_atoi_vm(game->arena, &cursor->current, TYPE_LEN).v_1;
	arg1 = ft_get_arg(game, type.arg1, false);
	arg2 = ft_get_arg(game, type.arg2, true);
	if(arg1 == 0)
		cursor->carry = true;
	cursor->regs[arg2 - 1] = arg1;
	return 0;
}