//
// Created by xel on 13.03.2020.
//

#ifndef COREWAR_H
#define COREWAR_H

# include "op.h"
#include "libft.h"

typedef struct s_game
{
	void 			*arena;
	t_list			*cursor;
}				t_game;

t_game *ft_init_game();
void ft_usage();
void ft_print_error(int err);
void ft_logo();
void ft_game_over(t_game **game);
void ft_print_arena(void *arena, size_t size);
#endif
