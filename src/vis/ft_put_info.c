/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "vis.h"

static void	ft_put_controls_info(t_window *win, t_point begin, t_point start)
{
	mlx_string_put(win->mlx, win->win, start.x, start.y, \
	C_WHITE, "Press \'+\' to increase speed");
	start.y += 25;
	mlx_string_put(win->mlx, win->win, start.x, start.y, \
	C_WHITE, "and \'-\' to decrease speed");
}

static void	ft_put_hint(t_window *win, t_point begin, t_point start)
{
	mlx_string_put(win->mlx, win->win, start.x, start.y, \
	C_WHITE, "for live op");
	start.x -= 10;
	start.y += 12;
	start.color = C_RED;
	ft_draw_solid_circle(win, start, 4);
	start.color = C_IRED;
	ft_draw_circle(win, start, 4);
	start.y += 25;
	start.x = begin.x + 30;
	mlx_string_put(win->mlx, win->win, start.x, start.y, \
	C_WHITE, "for carry");
	start.x -= 10;
	start.y += 12;
	start.color = C_RED;
	ft_draw_solid_circle(win, start, 4);
	start.color = C_IRED;
	ft_draw_solid_circle(win, start, 2);
}

static void	ft_put_next_string(t_window *win, t_point start, \
								char *str, int32_t nbr)
{
	char	*nbr_str;

	mlx_string_put(win->mlx, win->win, start.x, start.y, C_WHITE, str);
	start.x += 170;
	nbr_str = ft_itoa(nbr);
	mlx_string_put(win->mlx, win->win, start.x, start.y, C_CYAN, nbr_str);
	free(nbr_str);
}

void		ft_put_info(t_window *win, t_point begin)
{
	t_point	start;

	start.y = begin.y + 30;
	start.x = begin.x + 15;
	ft_put_next_string(win, start, "Cycle", win->game->cycle);
	start.y += 60;
	start.x = begin.x + 15;
	ft_put_next_string(win, start, "Doomsdays", win->game->doomsday_count);
	start.y += 60;
	start.x = begin.x + 15;
	ft_put_next_string(win, start, "Total cycles", win->game->total_cycles);
	start.y += 60;
	start.x = begin.x + 15;
	ft_put_next_string(win, start, "Cycles to die", win->game->cycles_to_die);
	start.y += 60;
	start.x = begin.x + 15;
	ft_put_next_string(win, start, "Carry's count", win->game->cursors_count);
	start.y += 130;
	start.x = begin.x + 15;
	ft_put_controls_info(win, begin, start);
	start.y += 80;
	start.x = begin.x + 30;
	ft_put_hint(win, begin, start);
}
