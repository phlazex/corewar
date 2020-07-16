/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_H
# define VIS_H

# include "corewar.h"
# include <pthread.h>

# define WINDOW_HEIGHT 760
# define WINDOW_WIDTH  1280
# define WINDOW_TITLE "Corewar"
# define ESCAPE 53
# define PLUS	24
# define MINUS 27

# define WINDOW_LOGO "VIRTUAL MACHINE v1.4"
# define FONT_SIZE 7
# define LOGO_HEIGHT 49

# define C_MAGENTA 0XEC00FF
# define C_BLUE 0X0049FF
# define C_IBLUE 0Xffb600
# define C_CYAN 0X00FFDC
# define C_GREEN 0X51FF00
# define C_IGREEN 0Xae00ff
# define C_YELLOW 0XFFF700
# define C_IYELLOW 0X0008ff
# define C_ORANGE 0XFF8700
# define C_RED 0XFF0000
# define C_IRED 0x00ffff
# define C_WHITE 0XFFFFFF
# define C_BLACK 0X0
# define C_LGRAY 0xd3d3d3
# define C_DGRAY 0x565656

# define LOGO_Y 29
# define CHAMP_X 360
# define CHAMP_Y 29
# define CHAMP_WIDTH 200
# define CHAMP_HEIGHT 110
# define CHAMP_NEXT 230
# define INFO_X 29
# define INFO_Y 170
# define INFO_HEIGHT 560
# define INFO_WIDTH 300
# define FIELD_X 360
# define FIELD_Y 170
# define FIELD_HEIGHT 560
# define FIELD_WIDTH 890
# define BUTTON_X 450
# define BUTTON_Y 350
# define BUTTON_WIDTH 250
# define BUTTON_HEIGHT 60

# define CHAMP_MAXLEN 14

# define DEFAULT_DELAY 4000
# define MAX_DELAY 1000000
# define DELAY_STEP	2000

typedef struct		s_point
{
	int	x;
	int	y;
	int	color;
}					t_point;

typedef struct		s_champ
{
	int				id;
	int				color;
	size_t			life_count;
	size_t			lifes;

}					t_champ;

typedef struct		s_window
{
	void			*win;
	void			*mlx;
	t_game			*game;
	int				height;
	int				width;
	int				color;
	int				champ_count;
	t_bool			end;
	t_champ			champs[MAX_PLAYERS];
	t_color			*colors;
}					t_window;

t_point				ft_rewrite_point(int x, int y, int color);
void				ft_bresenham_line(t_point begin, t_point end, \
					t_window *win);
void				ft_fill_rectangle(t_window *win, t_point start, \
					t_point param);
void				ft_fill_gradient(t_window *win, t_point start, \
					t_point param);
void				ft_draw_rectangle(t_window *win, t_point start, \
					t_point param);
void				ft_draw_rectangle_with_name(t_window *win, t_point start, \
					t_point param, char *title);
void				ft_draw_solid_circle(t_window *win, t_point start, int rad);
void				ft_draw_circle(t_window *win, t_point start, int rad);
void				ft_draw_champion(t_window *win, t_point begin, \
					int color, int i);
int					ft_get_color(int begin_color, int end_color, \
					double percent);
void				ft_delete_window(t_window **window);
t_window			*ft_init_window(t_game *game);
int					ft_key_press(int key, void *param);
void				ft_put_logo(t_window *win, int x, int y);
void				ft_put_info(t_window *win, t_point begin);
void				ft_draw_grid(t_window *win);
int					ft_close_window(void *ptr);
int					ft_redraw_game_field(t_window *win);
void				ft_draw_heart(t_window *win, t_point begin, int color);
void				ft_draw_start_field(t_window *win, t_point start);
int					ft_check_color(int color);
void				ft_check_lifes(t_window *win);
void				ft_draw_game_field(t_window *win, t_point start);
int					ft_mouse_hook(int button, int x, int y, void *win_ptr);

#endif
