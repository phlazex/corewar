/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

int	ft_key_press(int key, void *param)
{
	t_window	*win;

	win = (t_window *)param;
	if (key == PLUS)
		if (*(win->game->fps) > DELAY_STEP)
			*(win->game->fps) -= DELAY_STEP;
	if (key == MINUS)
		if (*(win->game->fps) < MAX_DELAY)
			*(win->game->fps) += DELAY_STEP;
	if (key == ESCAPE)
		ft_close_window((void *)win);
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, void *win_ptr)
{
	t_window	*win;
	t_point		begin;
	t_point		param;

	win = (t_window *)win_ptr;
	if (button == 1 && *(win->game->start) == false && \
	(x >= BUTTON_X && x <= BUTTON_X + BUTTON_WIDTH) && \
	(y >= BUTTON_Y && y <= BUTTON_Y + BUTTON_HEIGHT))
	{
		begin = ft_rewrite_point(FIELD_X + 15, FIELD_Y + 15, C_BLACK);
		param = ft_rewrite_point(FIELD_WIDTH - 30, FIELD_HEIGHT - 30, C_BLACK);
		ft_fill_rectangle(win, begin, param);
		ft_draw_start_field(win, begin);
		pthread_mutex_lock(win->game->mutex);
		*(win->game->start) = true;
		pthread_cond_signal(win->game->cv);
		pthread_mutex_unlock(win->game->mutex);
	}
	return (0);
}
