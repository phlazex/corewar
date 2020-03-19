#include "corewar.h"

static t_bool ft_check_types(void *data, int op, int *next)
{
	union u_types type;//
	char temp;
	t_bool ok;
	ok = true;
	int size;
	size = 2;
	op--;
	type.value = *(unsigned char*)data;
	if (type.ar3)
		ok = false;

	if (type.ar2 == REG_CODE)
	{
		if (0 == (op_tab[op].types[2] & 1))
			ok = false;
		size += 1;
	}
	if (type.ar2 == DIR_CODE)
	{
		if (0 == (op_tab[op].types[2] & 2))
			ok = false;
		size += op_tab[op].dir_size;
	}
	if (type.ar2 == IND_CODE)
	{
		if (0 == (op_tab[op].types[2] & 4))
			ok = false;
		size += IND_SIZE;
	}

	if (type.ar1 == REG_CODE)
	{
		if (0 == (op_tab[op].types[1] & 1))
			ok = false;
		size += 1;
	}
	if (type.ar1 == DIR_CODE )
	{
		if (0 == (op_tab[op].types[1] & 2))
			ok = false;
		size += op_tab[op].dir_size;
	}
	if (type.ar1 == IND_CODE)
	{
		if (0 == (op_tab[op].types[1] & 4))
			ok = false;
		size += IND_SIZE;
	}
	if (type.ar0 == REG_CODE)
	{
		if (0 == (op_tab[op].types[0] & 1))
			ok = false;
		size += 1;
	}
	if (type.ar0 == DIR_CODE)
	{
		if (0 == (op_tab[op].types[0] & 2))
			ok = false;
		size += op_tab[op].dir_size;
	}
	if (type.ar0 == IND_CODE )
	{
		if (0 == (op_tab[op].types[0] & 4))
			ok = false;
		size += IND_SIZE;
	}
	*next = size;

	return ok;
}

static t_bool ft_check_types2(t_game *game)
{
	union u_types type;//
	char temp;
	int op;
	t_cursor *cursor;
	cursor = (t_cursor*)game->cursor->content;
	t_bool ok;
	ok = true;
	int size;
	size = 2;
	op = cursor->op - 1;
	type.value = *(unsigned char*)(game->arena + cursor->current + 1);
	if (type.ar3)
		ok = false;

	if (type.ar2 == REG_CODE)
	{
		if (0 == (op_tab[op].types[2] & 1) || (*( char*)(game->arena + (cursor->current + size)% MEM_SIZE) < 1 ||
												*( char*)(game->arena + (cursor->current + size)% MEM_SIZE) > 16))
			ok = false;
		size += 1;
	}
	if (type.ar2 == DIR_CODE)
	{
		if (0 == (op_tab[op].types[2] & 2))
			ok = false;
		size += op_tab[op].dir_size;
	}
	if (type.ar2 == IND_CODE)
	{
		if (0 == (op_tab[op].types[2] & 4))
			ok = false;
		size += IND_SIZE;
	}

	if (type.ar1 == REG_CODE)
	{
		if (0 == (op_tab[op].types[1] & 1)  || (*( char*)(game->arena + (cursor->current + size)% MEM_SIZE) < 1 ||
												*( char*)(game->arena + (cursor->current + size)% MEM_SIZE) > 16))
			ok = false;
		size += 1;
	}
	if (type.ar1 == DIR_CODE )
	{
		if (0 == (op_tab[op].types[1] & 2))
			ok = false;
		size += op_tab[op].dir_size;
	}
	if (type.ar1 == IND_CODE)
	{
		if (0 == (op_tab[op].types[1] & 4))
			ok = false;
		size += IND_SIZE;
	}
	if (type.ar0 == REG_CODE)
	{
		if (0 == (op_tab[op].types[0] & 1) || (*( char*)(game->arena + (cursor->current + size)% MEM_SIZE) < 1 ||
											   *( char*)(game->arena + (cursor->current + size)% MEM_SIZE) > 16))
			ok = false;
		size += 1;
	}
	if (type.ar0 == DIR_CODE)
	{
		if (0 == (op_tab[op].types[0] & 2))
			ok = false;
		size += op_tab[op].dir_size;
	}
	if (type.ar0 == IND_CODE )
	{
		if (0 == (op_tab[op].types[0] & 4))
			ok = false;
		size += IND_SIZE;
	}
	cursor->step_to_next = (cursor->current + size) % MEM_SIZE;

	return ok;
}

static void ft_apply_op(t_game *game)
{
	((t_cursor*)game->cursor->content)->current =
	op_tab[((t_cursor*)game->cursor->content)->op].func(game, ((t_cursor*)game->cursor->content)->current);
}

static int ft_execute(t_game *game)
{
	t_cursor *cursor;

	cursor = (t_cursor*)game->cursor->content;
	if (cursor->op > 0x00 && cursor->op < 0x11)
	{
		if (op_tab[cursor->op].arg_type)
		{
			if (ft_check_types2(game))
				ft_apply_op(game);
			else
				cursor->current = cursor->step_to_next;
		}
	}
	else
		cursor->current = (cursor->current + 1) % MEM_SIZE;
	return 0;
}

static int main_loop(t_game *game)
{
	int len;
	t_cursor *cursor;

	len = game->cursors_count;
	while (len--)
	{
		cursor = (t_cursor*)game->cursor->content;
		if (cursor->ready == 0)
		{
			cursor->op = *(char*)(game->arena + cursor->current);
			if (cursor->op > 0x00 && cursor->op < 0x11)
				cursor->ready = op_tab[cursor->op].cycles;
		}
		if (cursor->ready > 0)
			cursor->ready--;
		if (cursor->ready == 0)
			ft_execute(game);
		game->cursor = game->cursor->next;
	}
	return 1;
}

static int ft_doomsday(t_game *game)
{
	int len;
	t_cursor *cursor;

	len = game->cursors_count;
	while (len--)
	{
		cursor = (t_cursor*)game->cursor->content;
		if (cursor->live_cycle > game->cycles_to_die ||
				game->cycles_to_die <= 0)
		{
			ft_lstd_pop_front(&game->cursor);
			(game->cursors_count)--;
		}
		else
			game->cursor = game->cursor->next;
	}
	if(game->check_live >= NBR_LIVE || game->checks_done > MAX_CHECKS)
	{
		game->cycles_to_die -= CYCLE_DELTA;
		game->checks_done = 0;
	}
	(game->checks_done)++;
	return 0;
}


void ft_battle(t_game *game)
{
	int cycle;

	cycle = 0;
	while (game->cursor)
	{
		cycle++;
		main_loop(game);

		if (cycle >= game->cycles_to_die)
		{
			ft_doomsday(game);
			cycle = 0;
		}
	}
}