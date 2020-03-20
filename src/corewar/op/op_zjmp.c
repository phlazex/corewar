#include "corewar.h"

size_t op_zjmp(t_game *game)
{
	t_cursor *cursor;
	size_t address;
	int arg1;
	cursor = (t_cursor*)game->cursor->content;
	address = cursor->current;
	cursor->current = (cursor->current + OP_LEN) % MEM_SIZE;
	arg1 = ft_get_arg(game, DIR_CODE, true);
	if(cursor->carry)
		cursor->current = (address + arg1 % IDX_MOD) % MEM_SIZE;
}