/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"
#include "mlx.h"

static void	ft_draw_players(t_window *win, t_point begin, t_point end, int i)
{
	int	color;

	win->champs[i].id = i + 1;
	if (i == 0)
	{
		ft_draw_rectangle(win, begin, end);
		color = C_RED;
	}
	else if (i == 1)
	{
		ft_draw_rectangle(win, begin, end);
		color = C_YELLOW;
	}
	else if (i == 2)
	{
		ft_draw_rectangle(win, begin, end);
		color = C_GREEN;
	}
	else
	{
		ft_draw_rectangle(win, begin, end);
		color = C_BLUE;
	}
	ft_draw_champion(win, begin, color, i);
}

static void	ft_draw_first_greeting(t_window *win)
{
	t_point	begin;
	t_point	param;

	mlx_string_put(win->mlx, win->win, FIELD_X + 35, FIELD_Y + 35, \
	C_CYAN, "Welcome to the Corewar Virtual machine!");
	mlx_string_put(win->mlx, win->win, FIELD_X + 35, FIELD_Y + 65, \
	C_CYAN, "Click \"START\" to begin game");
	begin = ft_rewrite_point(BUTTON_X, BUTTON_Y, C_WHITE);
	param = ft_rewrite_point(BUTTON_WIDTH, BUTTON_HEIGHT, C_WHITE);
	ft_draw_rectangle(win, begin, param);
	mlx_string_put(win->mlx, win->win, BUTTON_X + 85, BUTTON_Y + 18, \
	C_WHITE, "S T A R T");
}

static void	ft_draw_grid_2(t_window *win)
{
	t_point	begin;
	t_point	end;

	begin = ft_rewrite_point(INFO_X, INFO_Y, C_WHITE);
	end = ft_rewrite_point(INFO_WIDTH, INFO_HEIGHT, C_WHITE);
	ft_draw_rectangle_with_name(win, begin, end, "Game info");
	ft_put_info(win, begin);
	begin.x = FIELD_X;
	end.x = FIELD_WIDTH;
	end.y = FIELD_HEIGHT;
	ft_draw_rectangle_with_name(win, begin, end, "Game field");
	mlx_pixel_put(win->mlx, win->win, begin.x, begin.y, C_WHITE);
	begin.x += 15;
	begin.y += 15;
	ft_draw_first_greeting(win);
}

void		ft_draw_grid(t_window *win)
{
	t_point	begin;
	t_point	end;
	int		i;

	begin = ft_rewrite_point(CHAMP_X, LOGO_Y, C_WHITE);
	ft_put_logo(win, begin.y + 5, begin.y + 10);
	end = ft_rewrite_point(CHAMP_WIDTH, CHAMP_HEIGHT, C_WHITE);
	i = 0;
	while (++i < 5)
	{
		if (win->game->input->hero_list[i - 1].id)
		{
			ft_draw_players(win, begin, end, i - 1);
			win->champ_count++;
		}
		begin.x += CHAMP_NEXT;
	}
	ft_draw_grid_2(win);
}
