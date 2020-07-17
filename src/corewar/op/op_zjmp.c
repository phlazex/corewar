#include "corewar.h"

t_err op_zjmp(t_game *game)
{
	t_cursor *cursor;
	int32_t arg;

	cursor = game->cursor;
	cursor->current = ft_mod(cursor->pc + OP_LEN, MEM_SIZE);
	arg = ft_get_data(game, DIR_CODE);
	if(cursor->carry)
		cursor->current = ft_mod(cursor->pc + arg % IDX_MOD, MEM_SIZE);
	return (success);
}