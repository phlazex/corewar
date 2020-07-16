/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_battle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwolf <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by hwolf             #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by hwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "vis.h"
#include "corewar_op.h"
#include <unistd.h>

static t_err	main_loop(t_game *game)
{
	t_cursor	*cursor;
	t_err		err;

	err = success;
	game->cursor = game->head;
	while (game->cursor)
	{
		cursor = game->cursor;
		if (game->color[game->cursor->pc % MEM_SIZE] > grey && \
			game->color[game->cursor->pc % MEM_SIZE] < l_blue)
			game->color[game->cursor->pc % MEM_SIZE] -= 5;
		if (!cursor->occupy)
		{
			cursor->op = *(char*)(game->arena + cursor->pc);
			if (cursor->op > 0x00 && cursor->op < 0x11)
				cursor->occupy = g_op_tab[cursor->op - 1].cycles;
		}
		cursor->occupy -= (cursor->occupy) ? 1 : 0;
		if (!cursor->occupy)
			err = ft_execute(game);
		if (cursor->alive && game->color[game->cursor->pc % MEM_SIZE] < i_blue)
			game->color[game->cursor->pc % MEM_SIZE] += 5;
		game->cursor = game->cursor->next;
	}
	return (err);
}
void            ft_battle_helper(t_game *game){
    ft_doomsday(game);
    if (game->check_live >= NBR_LIVE || game->checks_done >= MAX_CHECKS)
    {
        game->cycles_to_die -= CYCLE_DELTA;
        game->checks_done = 0;
    }
    if (game->input->log)
        ft_log_game(game);
    game->check_live = 0;
    game->cycle = 0;
}

t_bool			ft_battle(t_game *game)
{
	if (game->input->log)
		ft_log_game(game);
	while (game->head)
	{
		game->cycle++;
		game->total_cycles++;
		main_loop(game);
		if (game->cycle >= game->cycles_to_die)
            ft_battle_helper(game);
		if (game->total_cycles == game->input->dump)
			return (true);
		usleep(*(game->fps));
	}
	if (game->input->dump == 0)
		return (true);
	return (false);
}
