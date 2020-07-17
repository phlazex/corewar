/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_game_field.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

static void	ft_redraw_circles(t_window *win, t_point *begin, int rad, int *k)
{
	win->colors[*k] = win->game->color[*k];
	if (win->game->color[*k] > grey && win->game->color[*k] < l_blue)
	{
		begin->color = ft_check_color(win->game->color[*k]);
		ft_draw_solid_circle(win, *begin, rad - 2);
	}
	else if (win->game->color[*k] < i_blue)
	{
		begin->color = ft_check_color(win->game->color[*k]);
		ft_draw_solid_circle(win, *begin, rad);
	}
	else
	{
		begin->color = ft_check_color(win->game->color[*k] - 10);
		ft_draw_solid_circle(win, *begin, rad);
		begin->color = ft_check_color(win->game->color[*k]);
		ft_draw_circle(win, *begin, rad);
		win->game->color[*k] -= 10;
	}
}

static void	ft_redraw_line(t_window *win, t_point *begin, int rad, int *k)
{
	int	j;

	j = 1;
	while (j < 83 && *k < MEM_SIZE)
	{
		if (win->game->color[*k] != win->colors[*k])
			ft_redraw_circles(win, begin, rad, k);
		begin->x += 10;
		j++;
		*k = *k + 1;
	}
}

void		ft_draw_game_field(t_window *win, t_point start)
{
	t_point	begin;
	int		i;
	int		rad;
	int		k;

	rad = 4;
	start.x += 24;
	start.y += 22;
	begin = ft_rewrite_point(start.x, start.y, C_WHITE);
	i = -1;
	k = 0;
	while (++i < 51)
	{
		ft_redraw_line(win, &begin, rad, &k);
		begin.x = start.x;
		begin.y += 10;
	}
	if (win->game->doomsday == true)
		ft_check_lifes(win);
}
