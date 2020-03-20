#include "corewar.h"

int ft_get_arg(t_game *game, int arg_type, t_bool idx)
{
	t_cursor *cursor;
	int op;
	int arg;
	arg = 0;
	cursor = (t_cursor*)game->cursor->content;
	op = cursor->op - 1;
	if (arg_type == DIR_CODE)
	{
		if (op_tab[op].dir_size == 2)
			arg = ft_atoi_vm(game->arena, &cursor->current,
							 op_tab[op].dir_size).v_2;
		else
			arg = ft_atoi_vm(game->arena, &cursor->current,
							 op_tab[op].dir_size).v_4;
	}
	if(arg_type== IND_CODE)
	{
		arg = ft_atoi_vm(game->arena, &cursor->current, IND_SIZE).v_2;
		if (idx)
			arg %= IDX_MOD;
	}
	if(arg_type == REG_CODE)
		arg = ft_atoi_vm(game->arena, &cursor->current, REG_LEN).v_4;
	return arg;
}

t_err ft_clone_cursor(t_game *game, size_t address)
{

	t_cursor *new_cursor;
	t_cursor *cursor;
	cursor = (t_cursor*)game->cursor->content;
	if (!(new_cursor = ft_new_cursor()))
		return (no_memory);
	ft_memcpy(new_cursor, cursor, sizeof(*cursor));
	game->cursors_count++;
	new_cursor->current = address;
	ft_lstd_push_front(&game->cursor, ft_lstd_wrap(new_cursor, sizeof(*new_cursor)));
	return (success);
}