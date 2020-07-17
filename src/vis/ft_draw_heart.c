/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_heart.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

static void	ft_draw_heart_2(t_window *win, t_point begin, t_point param)
{
	begin.x += 8;
	begin.y += 8;
	param.x = 12;
	param.y = 8;
	ft_fill_rectangle(win, begin, param);
	begin.x += 4;
	begin.y += 8;
	param.x = 4;
	param.y = 4;
	ft_fill_rectangle(win, begin, param);
	begin.color = C_WHITE;
	begin.x += 8;
	begin.y -= 16;
	ft_fill_rectangle(win, begin, param);
}

void		ft_draw_heart(t_window *win, t_point begin, int color)
{
	t_point	param;

	begin.color = color;
	param.x = 8;
	param.y = 16;
	ft_fill_rectangle(win, begin, param);
	begin.x += 12;
	ft_fill_rectangle(win, begin, param);
	begin.x -= 16;
	begin.y += 4;
	param.x = 28;
	param.y = 8;
	ft_fill_rectangle(win, begin, param);
	ft_draw_heart_2(win, begin, param);
}
