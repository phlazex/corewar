/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redraw_game_field.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "vis.h"
#include <unistd.h>

static void	ft_write_winner(t_window *win, t_point begin)
{
	char	*name;
	char	temp;

	begin.color = ft_check_color(win->game->winner->id);
	name = win->game->winner->header.prog_name;
	temp = name[63];
	name[63] = '\0';
	mlx_string_put(win->mlx, win->win, begin.x + 180, \
	begin.y +  60, begin.color, name);
	name[63] = temp;
	name = &name[64];
	mlx_string_put(win->mlx, win->win, begin.x + 180, \
	begin.y +  80, begin.color, name);
	name = win->game->winner->header.comment;
	temp = name[63];
	name[63] = '\0';
	mlx_string_put(win->mlx, win->win, begin.x + 180, \
	begin.y +  110, begin.color, name);
	name[63] = temp;
	name = &name[64];
	temp = name[63];
	name[63] = '\0';
	mlx_string_put(win->mlx, win->win, begin.x + 180, \
	begin.y +  130, begin.color, name);
	name[63] = temp;
}

static void	ft_write_result(t_window *win)
{
	t_point	begin;
	t_point	param;

	win->end = true;
	usleep(50000);
	begin = ft_rewrite_point(FIELD_X + 15, FIELD_Y + 15, C_BLACK);
	param = ft_rewrite_point(FIELD_WIDTH - 30, FIELD_HEIGHT - 30, C_BLACK);
	ft_fill_rectangle(win, begin, param);
	mlx_string_put(win->mlx, win->win, begin.x + 20, \
	begin.y +  20, C_CYAN, "The game is over!");
	mlx_string_put(win->mlx, win->win, begin.x + 20, \
	begin.y +  60, C_CYAN, "The winner is:");
	ft_write_winner(win, begin);
	mlx_string_put(win->mlx, win->win, begin.x + 20, \
	begin.y +  110, C_CYAN, "Comment:");
}

static void	ft_write_string(t_window *win, t_point begin, int nbr)
{
	char *nbr_str;

	nbr_str = ft_itoa(nbr);
	mlx_string_put(win->mlx, win->win, begin.x, begin.y, C_CYAN, nbr_str);
	free(nbr_str);
}

static void	ft_rewrite_info(t_window *win, t_point *begin, t_point *param)
{
	*begin = ft_rewrite_point(INFO_X + 185, INFO_Y + 30, C_BLACK);
	*param = ft_rewrite_point(110, 22, C_BLACK);
	ft_fill_rectangle(win, *begin, *param);
	ft_write_string(win, *begin, win->game->cycle);
	begin->y += 60;
	ft_fill_rectangle(win, *begin, *param);
	ft_write_string(win, *begin, win->game->doomsday_count);
	begin->y += 60;
	ft_fill_rectangle(win, *begin, *param);
	ft_write_string(win, *begin, win->game->total_cycles);
	if (win->game->cycles_to_die >= 0)
	{
		begin->y += 60;
		ft_fill_rectangle(win, *begin, *param);
		ft_write_string(win, *begin, win->game->cycles_to_die);
	}
	begin->y += 60;
	ft_fill_rectangle(win, *begin, *param);
	ft_write_string(win, *begin, win->game->cursors_count);
}

int			ft_redraw_game_field(t_window *win)
{
	t_point	begin;
	t_point	param;

	if (win->game->head && *(win->game->start))
	{
		ft_rewrite_info(win, &begin, &param);
		begin = ft_rewrite_point(FIELD_X + 15, FIELD_Y + 15, C_BLACK);
		ft_draw_game_field(win, begin);
	}
	else if (win->end == false && *(win->game->start))
		ft_write_result(win);
	return (0);
}
