/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_champions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"
#include "mlx.h"

static void	ft_draw_lifes(t_window *win, t_point begin, int color)
{
	int i;

	i = 0;
	while (++i < 6)
	{
		ft_draw_heart(win, begin, color);
		begin.x += 35;
	}
}

static void	ft_print_multiline(t_window *win, t_point begin, \
								int maxlen, char *str)
{
	char	temp;
	int		len;

	len = ft_strlen(str);
	if (len > maxlen)
	{
		temp = str[maxlen - 3];
		str[maxlen - 3] = '\0';
		mlx_string_put(win->mlx, win->win, begin.x, begin.y, begin.color, str);
		begin.x += (maxlen - 3) * 10;
		mlx_string_put(win->mlx, win->win, begin.x, begin.y, \
		begin.color, "...");
		str[maxlen - 3] = temp;
	}
	else
		mlx_string_put(win->mlx, win->win, begin.x, begin.y, begin.color, str);
}

static void	ft_draw_champ_name(t_window *win, t_point begin, \
								int maxlen, char *name)
{
	int		len;
	t_point end;
	t_point start;

	len = ft_strlen(name);
	len = (len > maxlen) ? maxlen : len;
	begin.x += 5;
	begin.y -= 8;
	end.x = len * 12;
	end.y = 22;
	start = ft_rewrite_point(begin.x, begin.y, C_BLACK);
	ft_fill_rectangle(win, start, end);
	begin.x += 11;
	begin.y -= 5;
	ft_print_multiline(win, begin, CHAMP_MAXLEN, name);
}

void		ft_draw_champion(t_window *win, t_point begin, int color, int i)
{
	char	*name;

	begin.color = color;
	name = win->game->input->hero_list[i].header.prog_name;
	ft_draw_champ_name(win, begin, CHAMP_MAXLEN, name);
	begin.x += 20;
	begin.y += 20;
	name = win->game->input->hero_list[i].header.comment;
	begin.color = color;
	ft_print_multiline(win, begin, CHAMP_MAXLEN, name);
	begin.y += 45;
	win->champs[i].color = color;
	win->champs[i].lifes = 5;
	win->champs[i].life_count = 0;
	ft_draw_lifes(win, begin, color);
}
