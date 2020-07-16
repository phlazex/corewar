/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_rectangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"
#include "libft.h"
#include "mlx.h"

void	ft_fill_rectangle(t_window *win, t_point start, t_point param)
{
	t_point	end;
	int		i;

	i = -1;
	end = start;
	end.x += param.x;
	while (++i < param.y)
	{
		ft_bresenham_line(start, end, win);
		start.y++;
		end.y++;
	}
}

void	ft_fill_gradient(t_window *win, t_point start, t_point param)
{
	t_point	end;
	t_point	begin;
	double	percent;
	int		i;

	i = -1;
	end = start;
	end.x += param.x;
	begin = start;
	while (++i < param.y)
	{
		ft_bresenham_line(start, end, win);
		start.y++;
		end.y++;
		percent = (double)(start.y - begin.y) / (double)(param.y);
		start.color = ft_get_color(begin.color, param.color, percent);
	}
}

void	ft_draw_rectangle(t_window *win, t_point start, t_point param)
{
	t_point	begin;
	t_point	end;

	begin = start;
	end.color = begin.color;
	end.x = begin.x + param.x;
	end.y = begin.y;
	ft_bresenham_line(begin, end, win);
	begin = end;
	end.y = begin.y + param.y;
	ft_bresenham_line(begin, end, win);
	begin = end;
	end.x = begin.x - param.x;
	ft_bresenham_line(begin, end, win);
	ft_bresenham_line(start, end, win);
}

/*
** Works correctly only if there's enough place for all characters in title
*/

void	ft_draw_rectangle_with_name(t_window *win, t_point start, \
									t_point param, char *title)
{
	t_point	begin;
	t_point	end;

	ft_draw_rectangle(win, start, param);
	begin.x = start.x + 5;
	begin.y = start.y - 8;
	end.x = ft_strlen(title) * 11;
	end.y = 22;
	begin.color = C_BLACK;
	ft_fill_rectangle(win, begin, end);
	begin.x = start.x + 11;
	begin.y = start.y - 12;
	mlx_string_put(win->mlx, win->win, begin.x, begin.y, C_WHITE, title);
}
