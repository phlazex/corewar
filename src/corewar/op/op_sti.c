#include "corewar.h"

t_err op_sti(t_game *game)
{
	union u_types type;
	t_cursor *cursor;
	int32_t arg1;
	int32_t arg2;
	int32_t arg3;

	cursor = game->cursor;
	cursor->current = ft_mod(cursor->pc + OP_LEN, MEM_SIZE);
	type.value = ft_atoi_vm(game->arena, &cursor->current, TYPE_LEN).v_1;
	arg1 = ft_get_data(game, type.args.arg1);
	arg2 = ft_get_arg(game, type.args.arg2, true);
	arg3 = ft_get_arg(game, type.args.arg3, true);
	ft_itoa_vm(game->arena, cursor->pc + (arg3 + arg2) % IDX_MOD, cursor->regs[arg1 - 1]);
    ft_past_reg(game, cursor, (cursor->pc + (arg3 + arg2) % IDX_MOD) % MEM_SIZE);
	return (success);
}