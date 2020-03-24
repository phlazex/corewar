#include "corewar.h"

t_err op_fork(t_game *game)
{
	t_cursor *cursor;
	int32_t arg;

	cursor = game->cursor;
	cursor->current = ft_mod(cursor->pc + OP_LEN, MEM_SIZE);
	arg = ft_get_data(game, DIR_CODE) % IDX_MOD;
	return ft_clone_cursor(game, cursor->pc + arg);
}