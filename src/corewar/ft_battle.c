#include "ft_printf.h"
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
	if (type.arg4)
		ok = false;

	if (type.arg3 == REG_CODE)
	{
		if (0 == (op_tab[op].types[2] & 1))
			ok = false;
		size += 1;
	}
	if (type.arg3 == DIR_CODE)
	{
		if (0 == (op_tab[op].types[2] & 2))
			ok = false;
		size += op_tab[op].dir_size;
	}
	if (type.arg3 == IND_CODE)
	{
		if (0 == (op_tab[op].types[2] & 4))
			ok = false;
		size += IND_SIZE;
	}

	if (type.arg2 == REG_CODE)
	{
		if (0 == (op_tab[op].types[1] & 1))
			ok = false;
		size += 1;
	}
	if (type.arg2 == DIR_CODE )
	{
		if (0 == (op_tab[op].types[1] & 2))
			ok = false;
		size += op_tab[op].dir_size;
	}
	if (type.arg2 == IND_CODE)
	{
		if (0 == (op_tab[op].types[1] & 4))
			ok = false;
		size += IND_SIZE;
	}
	if (type.arg1 == REG_CODE)
	{
		if (0 == (op_tab[op].types[0] & 1))
			ok = false;
		size += 1;
	}
	if (type.arg1 == DIR_CODE)
	{
		if (0 == (op_tab[op].types[0] & 2))
			ok = false;
		size += op_tab[op].dir_size;
	}
	if (type.arg1 == IND_CODE )
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
	union u_types type;
	int op;
	t_cursor *cursor;
	cursor = game->cursor;
	t_bool ok;
	ok = true;
	int size;
	size = 2;
	op = cursor->op - 1;

	type.value = *(unsigned char*)(game->arena + cursor->current + 1);
	if (type.arg4)
		ok = false;

	if (type.arg1 == REG_CODE)
	{
		if (0 == (op_tab[op].types[0] & 1) || (*( char*)(game->arena + (cursor->current + size) % MEM_SIZE) < 1 ||
											   *( char*)(game->arena + (cursor->current + size) % MEM_SIZE) > 16))
			ok = false;
		size += 1;
	}
	if (type.arg1 == DIR_CODE)
	{
		if (0 == (op_tab[op].types[0] & 2))
			ok = false;
		size += op_tab[op].dir_size;
	}
	if (type.arg1 == IND_CODE )
	{
		if (0 == (op_tab[op].types[0] & 4))
			ok = false;
		size += IND_SIZE;
	}

	if (type.arg2 == REG_CODE)
	{
		if (0 == (op_tab[op].types[1] & 1)  || (*( char*)(game->arena + (cursor->current + size)% MEM_SIZE) < 1 ||
												*( char*)(game->arena + (cursor->current + size)% MEM_SIZE) > 16))
			ok = false;
		size += 1;
	}
	if (type.arg2 == DIR_CODE )
	{
		if (0 == (op_tab[op].types[1] & 2))
			ok = false;
		size += op_tab[op].dir_size;
	}
	if (type.arg2 == IND_CODE)
	{
		if (0 == (op_tab[op].types[1] & 4))
			ok = false;
		size += IND_SIZE;
	}

	if (type.arg3 == REG_CODE)
	{
		if (0 == (op_tab[op].types[2] & 1) || (*( char*)(game->arena + (cursor->current + size)% MEM_SIZE) < 1 ||
											   *( char*)(game->arena + (cursor->current + size)% MEM_SIZE) > 16))
			ok = false;
		size += 1;
	}
	if (type.arg3 == DIR_CODE)
	{
		if (0 == (op_tab[op].types[2] & 2))
			ok = false;
		size += op_tab[op].dir_size;
	}
	if (type.arg3 == IND_CODE)
	{
		if (0 == (op_tab[op].types[2] & 4))
			ok = false;
		size += IND_SIZE;
	}
	cursor->step_to_next = (cursor->current + size) % MEM_SIZE;

	return ok;
}

static void ft_apply_op(t_game *game)
{
//	ft_log_cursor(fd_game);
	game->cursor->op_adr = game->cursor->current;
	op_tab[((t_cursor*)game->cursor)->op - 1].func(game);
}

static int ft_execute(t_game *game)
{
	t_cursor *cursor;

	cursor = game->cursor;
	if (cursor->op > 0x00 && cursor->op < 0x11)
	{
		if (op_tab[cursor->op - 1].arg_type)
		{
			if (ft_check_types2(game))
				ft_apply_op(game);
			else
				cursor->current = cursor->step_to_next;
		}
		else
			ft_apply_op(game);
	}
	else
		cursor->current = (cursor->current + 1) % MEM_SIZE;
	return 0;
}

static int main_loop(t_game *game)
{
	t_cursor *cursor;
	game->cursor = game->head;
	size_t temp;
	while (game->cursor)
	{
		cursor = game->cursor;
		if (cursor->ready == 0)
		{
			cursor->op = *(char*)(game->arena + cursor->current);
			if (cursor->op > 0x00 && cursor->op < 0x11)
				cursor->ready = op_tab[cursor->op - 1].cycles;

		}
		if (cursor->ready > 0)
			cursor->ready--;
		if (cursor->ready == 0)
		{
			temp = cursor->current;
			ft_execute(game);
//			ft_log_cursor(game, temp);
		}
		game->cursor = game->cursor->next;
	}
	return 1;
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
		if(game->head == game->cursor)
		{
			game->head = game->head->next;
			ft_memdel((void **) &game->cursor);
			game->cursor = game->head;
		} else
			ft_printf(RED"\n\nALARM!!!!! ALARM!!!\n\n"RESET);
	}

}
static int ft_doomsday(t_game *game)
{

	t_cursor *cursor;

	(game->checks_done)++;
	game->cursor = game->head;
	t_cursor *prev; //temp
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
	if(game->check_live >= NBR_LIVE || game->checks_done >= MAX_CHECKS)
	{
		game->cycles_to_die -= CYCLE_DELTA;
		game->checks_done = 0;
	}
	return 0;
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
			ft_log_game(game);
			game->check_live = 0;
			game->cycle = 0;
		}

	}
}