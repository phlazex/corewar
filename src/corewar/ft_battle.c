#include "ft_printf.h"
#include "corewar.h"
#include "corewar_op.h"

static t_bool ft_check_arg(t_game *game, unsigned char type, char index)
{
	int32_t value;
	int32_t op;

	op = game->cursor->op - 1;
	if (type == REG_CODE)
	{
		value = ft_atoi_vm(game->arena, &game->cursor->current, TYPE_LEN).v_1;
		if ((g_op_tab[op].types[index] & 1) && value > 0 && value < 0x11)
		 	return true;
	}
	if (type == DIR_CODE)
	{
		game->cursor->current += g_op_tab[op].dir_size;
		game->cursor->current = ft_mod(game->cursor->current, MEM_SIZE);
		if (g_op_tab[op].types[index] & 2)
			return (true);
	}
	if (type == IND_CODE )
	{
		game->cursor->current += IND_SIZE;
		game->cursor->current = ft_mod(game->cursor->current, MEM_SIZE);
		if (g_op_tab[op].types[index] & 4)
			return (true);
	}
	return (false);
}

static t_bool ft_check_types(t_game *game)
{
	union u_types type;
	int32_t op;
	t_bool ok;

	t_cursor *cursor;
	cursor = game->cursor;
	cursor->current = (cursor->pc + OP_LEN) % MEM_SIZE;
	type.value = ft_atoi_vm(game->arena, &cursor->current, TYPE_LEN).v_1;
	op = cursor->op - 1;
	ok = ft_check_arg(game, type.arg1, 0);
	if (g_op_tab[op].arg_count > 1)
		ok = ft_check_arg(game, type.arg2, 1) && ok;
	if (g_op_tab[op].arg_count > 2)
		ok = ft_check_arg(game, type.arg3, 2) && ok;
	if (type.arg4)
		ok = false;
	if (!ok)
		cursor->pc = cursor->current;
	return (ok);

}

static t_err ft_apply_op(t_game *game)
{
	t_err err;
	size_t temp;

	temp = game->cursor->pc;
	err = g_op_tab[((t_cursor*)game->cursor)->op - 1].func(game);
	game->cursor->pc = game->cursor->current;
	ft_log_cursor(game, temp);
	return (err);
}

static t_err ft_execute(t_game *game)
{
	t_cursor *cursor;
	t_err err;

	err = success;
	cursor = game->cursor;
	if (cursor->op > 0x00 && cursor->op < 0x11)
	{
		if (g_op_tab[cursor->op - 1].arg_type)
		{
			if (ft_check_types(game))
				err = ft_apply_op(game);
		}
		else
			err = ft_apply_op(game);
	}
	else
		cursor->pc = (cursor->pc + OP_LEN) % MEM_SIZE;
	return (err);
}

static t_err main_loop(t_game *game)
{
	t_cursor *cursor;
	t_err err;

	err = success;
	game->cursor = game->head;
	while (game->cursor)
	{
		cursor = game->cursor;
		if (!cursor->occupy)
		{
			cursor->op = *(char*)(game->arena + cursor->pc);
			if (cursor->op > 0x00 && cursor->op < 0x11)
				cursor->occupy = g_op_tab[cursor->op - 1].cycles;
		}
		if (cursor->occupy)
			cursor->occupy--;
		if (!cursor->occupy)
			err = ft_execute(game);
		game->cursor = game->cursor->next;
	}
	return (err);
}

static void ft_pop_cursor(t_game *game, t_cursor *prev)
{
	if (prev)
	{
		prev->next = game->cursor->next;
		ft_memdel((void **)&game->cursor);
		game->cursor = prev->next;
	}
	else
	{
		game->head = game->head->next;
		ft_memdel((void **) &game->cursor);
		game->cursor = game->head;
	}
}

static void ft_doomsday(t_game *game)
{

	t_cursor *cursor;
	t_cursor *prev;

	(game->checks_done)++;
	game->cursor = game->head;
	prev = NULL;
	while (game->cursor)
	{
		cursor = game->cursor;
		if (cursor->alive && game->cycles_to_die > 0)
		{
			cursor->alive = false;
			prev = game->cursor;
			game->cursor = game->cursor->next;
		}
		else
		{
			ft_pop_cursor(game, prev);
			(game->cursors_count)--;
		}
	}
}


void ft_battle(t_game *game)
{
	ft_log_game(game);
	while (game->head)
	{
		game->cycle++;
		game->total_cycles++;
		main_loop(game);
		if (game->cycle >= game->cycles_to_die)
		{
			ft_doomsday(game);
			if(game->check_live >= NBR_LIVE || game->checks_done >= MAX_CHECKS)
			{
				game->cycles_to_die -= CYCLE_DELTA;
				game->checks_done = 0;
			}
			ft_log_game(game);
			game->check_live = 0;
			game->cycle = 0;
		}
	}
}