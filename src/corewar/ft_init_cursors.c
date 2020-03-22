#include "corewar.h"


t_err ft_init_cursors(t_game *game)
{
	int i;
	t_cursor *cursor;
	i = game->player_count;
	while (i)
	{
		if (!(cursor = ft_new_cursor()))
			return (no_memory);
		cursor->id = game->cursors_count++;
		cursor->carry = false;
		cursor->regs[0] = -(i--); //need data??
		cursor->current = MEM_SIZE / game->player_count * i;
		cursor->alive = false;
		game->color[cursor->current] += 5;
		cursor->next = game->head;
		game->head = cursor;
//		ft_lstd_push_front(&game->head, ft_lstd_wrap(head, sizeof(*head)));
	}
	return (success);
}