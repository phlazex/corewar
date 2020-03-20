#include "corewar.h"

size_t op_fork(t_game *game)
{

	t_cursor *cursor;
	size_t address;
	int arg1;

	cursor = (t_cursor*)game->cursor->content;
	address = cursor->current;
	cursor->current = (cursor->current + OP_LEN) % MEM_SIZE;

	arg1 = ft_get_arg(game, DIR_CODE, true);
	ft_clone_cursor(game, (address + arg1) % MEM_SIZE);
	return 0;
}