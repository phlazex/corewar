//
// Created by xel on 13.03.2020.
//

#ifndef COREWAR_H
#define COREWAR_H

# include "op.h"
#include "libft.h"

typedef enum e_color
{
	white,
	red,
	blue,
	green,
	purple,
	grey
}			t_color;

typedef enum e_err
{
	success,
	no_memory,
	w_flag,
	w_file_name,
	w_player_number,
	w_format,
	dup_id,
	no_file,
	w_file_read,
	w_file_size,
	except_magic,
	exceed_size,
	wrong_psize


}			t_err;

typedef enum e_bool
{
	false,
	true
}			t_bool;

typedef enum e_op
{
	add
}			t_op;

typedef struct s_hero
{
	unsigned char	program[CHAMP_MAX_SIZE];
	int32_t 		id;
	header_t		header;
	char 			*file_name;
}					t_hero;

typedef struct	s_cursor
{
	int32_t 	id;
	t_bool		carry;
	t_op 		op;
	int32_t 	live_cycle;
	int32_t 	cycles_to_die;
	void 		*current;
	size_t 		step_to_next;
	int32_t 	*regs;
	t_color 	color;

}				t_cursor;

typedef struct s_game
{
	void 		*arena;
	t_list		*cursor;
	t_hero		*winner;
	int64_t 	total_cycles;
	int32_t 	check_live;
	int32_t 	cycles_to_die;
	int32_t 	checks_done;

}				t_game;

typedef struct	s_data
{
	int			flags;
	t_hero		hero_list[MAX_PLAYERS];
//	int			hero_id[MAX_PLAYERS];
}				t_data;


t_game *ft_init_game();
void ft_usage();

void ft_logo();
void *ft_game_over(t_game **game);


void ft_print_arena(void *arena);
void ft_print_error(t_err err);
void ft_print_regs(t_game *game);
t_err ft_parse_input(int argc, char **argv, t_data **data);
t_err ft_parse_hero(t_hero *hero, t_mem *mem);
u_int64_t ft_atoin(void *data, size_t size);
void ft_past_heroes();
void ft_init_cursors();
void ft_battle();
void ft_print_result();
void ft_print_memory(void *start, void *end, void *mark, void *tail);
#endif
