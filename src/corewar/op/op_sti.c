#include "corewar.h"

size_t op_sti(t_game *game)
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
	arg2 = ft_get_arg(game, type.arg2, true);
	arg3 = ft_get_arg(game, type.arg3, true);
	ft_itoa_vm(game->arena, cursor->op_adr + (arg3 +arg2) % IDX_MOD, cursor->regs[arg1 - 1]);
	return 0;
}