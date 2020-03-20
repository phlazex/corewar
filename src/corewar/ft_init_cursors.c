#include "corewar.h"


t_err ft_init_cursors(t_game *game)
{
	int i;
	t_cursor *cursor;
	i = 0;
	while (i <  game->player_count)
	{
		if (!(cursor = ft_new_cursor()))
			return (no_memory);
		cursor->id = (game->cursors_count)++;
		cursor->carry = false;
		cursor->current = MEM_SIZE / game->player_count * i;
		game->color[cursor->current] += 5;
		cursor->regs[0] = - (++i); //need data??

//		cursor->op = *(char*)cursor->current;
		ft_lstd_push_front(&game->cursor, ft_lstd_wrap(cursor, sizeof(*cursor)));
	}
	return (success);
}