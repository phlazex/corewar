#include "ft_printf.h"
#include "corewar.h"

t_err op_live(t_game *game)
{
	t_cursor *cursor;
	int32_t arg;

	cursor = game->cursor;
	cursor->current = ft_mod(cursor->pc + OP_LEN, MEM_SIZE);
	arg = ft_get_data(game, DIR_CODE);
	game->check_live++;
	cursor->alive = true;
	if (-arg > 0 && -arg <= MAX_PLAYERS)
	{
		if(game->hero_list[-arg - 1].id == -arg)
		{
			ft_set_color(white - arg);
			ft_printf(
					"A process shows that player %d (\"%s\") is alive"RESET"\n",
					-arg, (game->hero_list - arg - 1)->header.prog_name);
			game->winner = game->hero_list - arg - 1;
		}
	}
	return (success);
}
