#include "corewar.h"

size_t op_zjmp(t_game *game)
{
	t_cursor *cursor;
	int arg1;
	cursor = game->cursor;
	cursor->current = ft_mod(cursor->current + OP_LEN, MEM_SIZE);
	arg1 = ft_get_data(game, DIR_CODE);
	if(cursor->carry)
		cursor->current = ft_mod(cursor->op_adr + arg1 % IDX_MOD, MEM_SIZE);
	return 0;
}