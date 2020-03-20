#include "corewar.h"

size_t op_live(t_game *game)
{
	t_cursor *cursor;
	int arg1;
	cursor = (t_cursor*)game->cursor->content;
	cursor->current = (cursor->current + OP_LEN) % MEM_SIZE;
	arg1 = ft_get_arg(game, DIR_CODE, false);
	game->check_live++;
	cursor->live_cycle = game->cycle;
	if (-arg1 > 0 && -arg1 <= game->player_count)
	{
		game->hero_list[-arg1 - 1].live++;
		game->winner = game->hero_list - arg1 - 1;
	}
	return 0;
}
