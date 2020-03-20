#include "corewar.h"

size_t op_lldi(t_game* game)
{
	union u_types type;
	t_cursor *cursor;
	int arg1;
	int arg2;
	int arg3;
	cursor = (t_cursor*)game->cursor->content;
	cursor->current = (cursor->current + OP_LEN) % MEM_SIZE;
	type.value = ft_atoi_vm(game->arena, &cursor->current, TYPE_LEN).v_1;
	arg1 = ft_get_arg(game, type.arg1, true);
	arg2 = ft_get_arg(game, type.arg2, true);
	arg3 = ft_get_arg(game, type.arg3, true);
	if(type.arg1 == REG_CODE)
		arg1 = cursor->regs[arg1 - 1];
	if(type.arg2 == REG_CODE)
		arg2 = cursor->regs[arg2 - 1];
	cursor->regs[arg3 - 1] = (arg1 + arg2);
	return 0;
}