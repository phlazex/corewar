#include "corewar.h"

t_err op_st(t_game *game)
{
	union u_types type;
	t_cursor *cursor;
	int32_t arg1;
	int32_t arg2;

	cursor = game->cursor;
	cursor->current = ft_mod(cursor->pc + OP_LEN, MEM_SIZE);
	type.value = ft_atoi_vm(game->arena, &cursor->current, TYPE_LEN).v_1;
	arg1 = ft_get_data(game, type.args.arg1);
	arg2 = ft_get_data(game, type.args.arg2);
	if(type.args.arg2 == REG_CODE)
		cursor->regs[arg2 - 1] = cursor->regs[arg1 - 1];
	if(type.args.arg2 == IND_CODE) {
        ft_itoa_vm(game->arena, cursor->pc + arg2 % IDX_MOD, cursor->regs[arg1 - 1]);
        ft_past_reg(game, cursor, (cursor->pc + (arg2) % IDX_MOD) % MEM_SIZE);

    }
	return (success);
}
