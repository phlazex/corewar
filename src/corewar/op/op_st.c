#include "corewar.h"

size_t op_st(t_game *game)
{
	union u_types type;
	t_cursor *cursor;
	int arg1;
	int arg2;
	cursor = game->cursor;
	cursor->current = (cursor->current + OP_LEN) % MEM_SIZE;
	type.value = ft_atoi_vm(game->arena, &cursor->current, TYPE_LEN).v_1;
	arg1 = ft_get_data(game, type.arg1);
	arg2 = ft_get_data(game, type.arg2);
	if(type.arg2 == REG_CODE)
		cursor->regs[arg2 - 1] = cursor->regs[arg1 - 1];
	if(type.arg2 == IND_CODE)
		ft_itoa_vm(game->arena, cursor->op_adr + arg2 % IDX_MOD, cursor->regs[arg1 - 1]);
//		*(unsigned char*)(game->arena + (address + arg2 % IDX_MOD) % MEM_SIZE) = head->regs[arg1 - 1];
	return 0;
}
