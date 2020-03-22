#include "corewar.h"

size_t op_lfork(t_game *game)
{
	t_cursor *cursor;
	int32_t arg;
	cursor = game->cursor;
	cursor->current = (cursor->current + OP_LEN) % MEM_SIZE;
	arg = ft_get_data(game, DIR_CODE);
	ft_clone_cursor(game, cursor->op_adr + arg);
	return 0;
}