/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_circle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"
#include "mlx.h"

static void	ft_draw_lines(t_window *win, t_point *start, \
							t_point *end, t_point xy)
{
	end->x = start->x + xy.x;
	end->y = start->y + xy.y;
	ft_bresenham_line(*start, *end, win);
	end->y = start->y - xy.y;
	ft_bresenham_line(*start, *end, win);
	end->x = start->x - xy.x;
	ft_bresenham_line(*start, *end, win);
	end->y = start->y + xy.y;
	ft_bresenham_line(*start, *end, win);
}

static void	ft_draw_pixel(t_window *win, t_point start, t_point xy)
{
	mlx_pixel_put(win->mlx, win->win, start.x + xy.x, \
	start.y + xy.y, start.color);
	mlx_pixel_put(win->mlx, win->win, start.x + xy.x, \
	start.y - xy.y, start.color);
	mlx_pixel_put(win->mlx, win->win, start.x - xy.x, \
	start.y + xy.y, start.color);
	mlx_pixel_put(win->mlx, win->win, start.x - xy.x, \
	start.y - xy.y, start.color);
}

void		ft_draw_circle(t_window *win, t_point start, int rad)
{
	t_point	xy;
	int		delta;
	int		error;

	xy.x = 0;
	xy.y = rad;
	delta = 1 - 2 * rad;
	error = 0;
	while (xy.y >= 0)
	{
		ft_draw_pixel(win, start, xy);
		error = 2 * (delta + xy.y) - 1;
		if ((delta < 0) && (error <= 0))
		{
			delta += 2 * ++(xy.x) + 1;
			continue;
		}
		if ((delta > 0) && (error > 0))
		{
			delta -= 2 * --(xy.y) + 1;
			continue;
		}
		delta += 2 * (++(xy.x) - (xy.y)--);
	}
}

void		ft_draw_solid_circle(t_window *win, t_point start, int rad)
{
	int		delta;
	int		error;
	t_point	end;
	t_point	xy;

	xy.x = 0;
	xy.y = rad;
	delta = 1 - 2 * rad;
	end = start;
	while (xy.y >= 0)
	{
		ft_draw_lines(win, &start, &end, xy);
		error = 2 * (delta + xy.y) - 1;
		if ((delta < 0) && (error <= 0))
		{
			delta += 2 * ++xy.x + 1;
			continue;
		}
		if ((delta > 0) && (error > 0))
		{
			delta -= 2 * --xy.y + 1;
			continue;
		}
		delta += 2 * (++xy.x - xy.y--);
	}
}
