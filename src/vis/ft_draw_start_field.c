/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_start_field.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

static void	ft_check_circle_color(t_window *win, \
t_point *begin, int rad, int *k)
{
	if (win->game->color[*k] > grey && win->game->color[*k] < i_grey)
	{
		begin->color = ft_check_color((int)win->game->color[*k] - 5);
		ft_draw_solid_circle(win, *begin, rad);
		begin->color = ft_check_color(win->game->color[*k]);
		ft_draw_solid_circle(win, *begin, rad - 2);
	}
	else
	{
		begin->color = ft_check_color(win->game->color[*k]);
		ft_draw_solid_circle(win, *begin, rad);
	}
	begin->x += 10;
	*k = *k + 1;
}

void		ft_draw_start_field(t_window *win, t_point start)
{
	t_point	begin;
	int		i;
	int		j;
	int		rad;
	int		k;

	rad = 4;
	start.x += 24;
	start.y += 22;
	begin = start;
	begin.color = C_WHITE;
	i = -1;
	k = 0;
	while (++i < 51)
	{
		j = 1;
		while (j < 83 && k < MEM_SIZE)
		{
			ft_check_circle_color(win, &begin, rad, &k);
			j++;
		}
		begin.x = start.x;
		begin.y += 10;
	}
	ft_memcpy(win->colors, win->game->color, MEM_SIZE * sizeof(t_color));
}
