/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doomsday.c                                      :+:      :+:    :+:   */
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

static void	ft_pop_cursor(t_game *game, t_cursor *prev)
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
		ft_memdel((void **)&game->cursor);
		game->cursor = game->head;
	}
}

void		ft_doomsday(t_game *game)
{
	t_cursor	*cursor;
	t_cursor	*prev;

	(game->checks_done)++;
	(game->doomsday_count)++;
	game->cursor = game->head;
	game->doomsday = true;
	prev = NULL;
	while (game->cursor)
	{
		cursor = game->cursor;
		if (cursor->alive && game->cycles_to_die > 0)
		{
			cursor->alive = false;
			if (game->color[game->cursor->pc % MEM_SIZE] > grey)
				game->color[game->cursor->pc % MEM_SIZE] -= 5;
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
