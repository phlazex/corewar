/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "vis.h"

static t_point	ft_find_delta(t_point begin, t_point end, int *error)
{
	t_point delta;

	delta.x = abs(end.x - begin.x);
	delta.y = abs(end.y - begin.y);
	*error = delta.x - delta.y;
	return (delta);
}

static t_point	ft_find_sign(t_point begin, t_point end)
{
	t_point sign;

	sign.x = (begin.x < end.x) ? 1 : -1;
	sign.y = (begin.y < end.y) ? 1 : -1;
	return (sign);
}

void			ft_bresenham_line(t_point begin, t_point end, t_window *win)
{
	t_point	delta;
	t_point	sign;
	int		error;
	int		error2;

	delta = ft_find_delta(begin, end, &error);
	sign = ft_find_sign(begin, end);
	mlx_pixel_put(win->mlx, win->win, end.x, end.y, end.color);
	while (begin.x != end.x || begin.y != end.y)
	{
		mlx_pixel_put(win->mlx, win->win, begin.x, begin.y, begin.color);
		error2 = error * 2;
		if (error2 > -delta.y)
		{
			error -= delta.y;
			begin.x += sign.x;
		}
		if (error2 < delta.x)
		{
			error += delta.x;
			begin.y += sign.y;
		}
	}
}
