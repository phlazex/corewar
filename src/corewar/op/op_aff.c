#include "ft_printf.h"
#include "corewar.h"

size_t op_aff(t_game* game)
{
	union u_types type;
	t_cursor *cursor;
	int arg1;
	cursor = (t_cursor*)game->cursor->content;
	cursor->current = (cursor->current + OP_LEN) % MEM_SIZE;
	type.value = ft_atoi_vm(game->arena, &cursor->current, TYPE_LEN).v_1;
	arg1 = ft_get_arg(game, type.arg1, true);
	ft_printf("%c", cursor[arg1 - 1]);
	return 0;
}