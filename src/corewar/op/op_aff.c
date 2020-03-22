#include "ft_printf.h"
#include "corewar.h"

t_err op_aff(t_game* game)
{
	union u_types type;
	t_cursor *cursor;
	int arg;
	cursor = game->cursor;
	cursor->current = ft_mod(cursor->current + OP_LEN, MEM_SIZE);
	type.value = ft_atoi_vm(game->arena, &cursor->current, TYPE_LEN).v_1;
	arg = ft_get_data(game, type.arg1);
	ft_printf("%c", cursor[arg - 1]);
	return (success);
}