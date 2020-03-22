#include "corewar.h"

t_err op_live(t_game *game)
{
	t_cursor *cursor;
	int32_t arg;

	cursor = game->cursor;
	cursor->current = ft_mod(cursor->current + OP_LEN, MEM_SIZE);
	arg = ft_get_data(game, DIR_CODE);
	game->check_live++;
	cursor->alive = true;
	cursor->live_cycle = game->total_cycles;
	if (-arg > 0 && -arg <= game->player_count)
	{
		game->hero_list[-arg - 1].live++;
		game->winner = game->hero_list - arg - 1;
	}
	return (success);
}
