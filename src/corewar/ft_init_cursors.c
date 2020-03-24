#include "corewar.h"


t_err ft_init_cursors(t_game *game)
{
	int i;
	int32_t count;
	t_cursor *cursor;
	i = MAX_PLAYERS;
	count = game->player_count;
	while (i--)
	{
		if(game->input->hero_list[i].id)
		{
			if (!(cursor = ft_new_cursor()))
				return (no_memory);
			cursor->id = game->cursors_count++;
			cursor->carry = false;
			cursor->regs[0] = -game->input->hero_list[i].id;
			cursor->pc = MEM_SIZE / game->player_count * (--count);
			cursor->alive = false;
			game->color[cursor->current] += 5;
			cursor->next = game->head;
			game->head = cursor;
		}
	}
	return (success);
}