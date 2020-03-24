#include "corewar.h"
#include "corewar_op.h"

int32_t ft_get_data(t_game *game, int arg_type)
{
	t_cursor *cursor;
	int op;
	int arg;
	arg = 0;
	cursor = game->cursor;
	op = cursor->op - 1;
	if (arg_type == DIR_CODE)
	{
		if (g_op_tab[op].dir_size == 2)
			arg = ft_atoi_vm(game->arena, &cursor->current,
							 g_op_tab[op].dir_size).v_2;
		else
			arg = ft_atoi_vm(game->arena, &cursor->current,
							 g_op_tab[op].dir_size).v_4;
	}
	if(arg_type== IND_CODE)
		arg = ft_atoi_vm(game->arena, &cursor->current, IND_SIZE).v_2;
	if(arg_type == REG_CODE)
		arg = ft_atoi_vm(game->arena, &cursor->current, REG_LEN).v_1;
	return arg;
}

int32_t ft_convert_arg(int32_t arg, t_game *game, int32_t arg_type, t_bool idx)
{
	size_t address;
	t_cursor *cursor;

	cursor = game->cursor;
	if (arg_type == DIR_CODE)
		return arg;
	if (arg_type == IND_CODE)
	{
		if (idx)
			arg %= IDX_MOD;
		address = (cursor->pc + arg);
		return ft_atoi_vm(game->arena, &address, REG_SIZE).v_4;
	}
	if (arg_type == REG_CODE)
		return cursor->regs[arg - 1];
	return arg;
}

t_err ft_clone_cursor(t_game *game, size_t address)
{

	t_cursor *new_cursor;
	t_cursor *cursor;

	address = ft_mod(address, MEM_SIZE);
	cursor = game->cursor;
	if (!(new_cursor = ft_new_cursor()))
		return (no_memory);
	ft_memcpy(new_cursor, cursor, sizeof(*cursor));
	new_cursor->id = game->head->id + 1;
	new_cursor->current = 0;
	new_cursor->pc = address;
	new_cursor->next = game->head;
	game->head = new_cursor;
	game->cursors_count++;
	return (success);
}

int32_t ft_get_arg(t_game *game, int32_t arg_type, t_bool idx)
{
	size_t arg;
	arg = ft_get_data(game, arg_type);
	return ft_convert_arg(arg, game, arg_type, idx);
}