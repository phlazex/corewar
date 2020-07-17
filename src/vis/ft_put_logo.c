/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_logo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "vis.h"

static void	ft_put_logo_4(t_window *win, t_point *begin, t_point *end)
{
	int		end_color;

	end_color = ft_get_color(C_ORANGE, C_MAGENTA,
	(double)(FONT_SIZE * 6) / (double)(LOGO_HEIGHT));
	*end = ft_rewrite_point(FONT_SIZE * 3, FONT_SIZE * 3, end_color);
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 25;
	ft_fill_gradient(win, *begin, *end);
	begin->x -= FONT_SIZE * 19;
	end_color = ft_get_color(C_ORANGE, C_MAGENTA,
	(double)(FONT_SIZE * 4) / (double)(LOGO_HEIGHT));
	*end = ft_rewrite_point(end->y, end->y - FONT_SIZE * 2, end_color);
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 13;
	ft_fill_gradient(win, *begin, *end);
}

static void	ft_put_logo_3(t_window *win, t_point *begin, t_point *end)
{
	int		end_color;

	end_color = C_MAGENTA;
	*end = ft_rewrite_point(FONT_SIZE * 3, FONT_SIZE * 2, end_color);
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 5;
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 12;
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 5;
	end->x += FONT_SIZE * 2;
	ft_fill_gradient(win, *begin, *end);
	begin->x -= FONT_SIZE * 9;
	end->x -= FONT_SIZE * 3;
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 25;
	ft_fill_gradient(win, *begin, *end);
}

static void	ft_put_logo_2(t_window *win, t_point *begin, t_point *end)
{
	int		end_color;

	end_color = ft_get_color(C_ORANGE, C_MAGENTA,
	(double)(FONT_SIZE * 5) / (double)(LOGO_HEIGHT));
	*end = ft_rewrite_point(end->x + FONT_SIZE, end->y - FONT_SIZE, end_color);
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 5;
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 3;
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 9;
	ft_fill_gradient(win, *begin, *end);
	begin->x -= FONT_SIZE * 6;
	end_color = C_MAGENTA;
	*end = ft_rewrite_point(end->x, end->y + FONT_SIZE, end_color);
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 19;
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 3;
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 3;
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 3;
	end_color = ft_get_color(C_ORANGE, C_MAGENTA,
	(double)(FONT_SIZE * 3) / (double)(LOGO_HEIGHT));
	*end = ft_rewrite_point(end->x, end->y - FONT_SIZE * 3, end_color);
}

static void	ft_put_logo_1(t_window *win, t_point *begin, t_point *end)
{
	int 	end_color;

	end_color = ft_get_color(C_ORANGE, C_MAGENTA,
	(double)(FONT_SIZE * 2) / (double)(LOGO_HEIGHT));
	*end = ft_rewrite_point(FONT_SIZE * 3, FONT_SIZE * 2, end_color);
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 5;
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 6;
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 6;
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 13;
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 6;
	ft_fill_gradient(win, *begin, *end);
	begin->x -= FONT_SIZE * 15;
	end_color = ft_get_color(C_ORANGE, C_MAGENTA,
	(double)(FONT_SIZE * 6) / (double)(LOGO_HEIGHT));
	*end = ft_rewrite_point(end->x - FONT_SIZE, FONT_SIZE * 6, end_color);
	ft_fill_gradient(win, *begin, *end);
	begin->x += FONT_SIZE * 5;
	ft_fill_gradient(win, *begin, *end);
	begin->x -= FONT_SIZE * 2;
	end->x -= FONT_SIZE;
	ft_fill_gradient(win, *begin, *end);
}

void		ft_put_logo(t_window *win, int x, int y)
{
	int		begin_color;
	t_point	begin;
	t_point	end;

	begin_color = C_ORANGE;
	begin = ft_rewrite_point(x + FONT_SIZE, y, begin_color);
	ft_put_logo_1(win, &begin, &end);
	begin_color = ft_get_color(C_ORANGE, C_MAGENTA,
	(double)(FONT_SIZE) / (double)(LOGO_HEIGHT));
	begin = ft_rewrite_point(x, y + FONT_SIZE, begin_color);
	ft_put_logo_2(win, &begin, &end);
	ft_fill_gradient(win, begin, end);
	begin.x -= FONT_SIZE * 25;
	ft_fill_gradient(win, begin, end);
	begin_color = ft_get_color(C_ORANGE, C_MAGENTA,
	(double)(FONT_SIZE * 4) / (double)(LOGO_HEIGHT));
	begin = ft_rewrite_point(x + FONT_SIZE, y + FONT_SIZE * 5, begin_color);
	ft_put_logo_3(win, &begin, &end);
	begin_color = ft_get_color(C_ORANGE, C_MAGENTA,
	(double)(FONT_SIZE * 3) / (double)(LOGO_HEIGHT));
	begin = ft_rewrite_point(x + FONT_SIZE * 12,
	y + FONT_SIZE * 3, begin_color);
	ft_put_logo_4(win, &begin, &end);
	mlx_string_put(win->mlx, win->win, x + 85, y + LOGO_HEIGHT + 10,
	C_MAGENTA, WINDOW_LOGO);
}
