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
	blue,
	green,
	purple,
	red,
	grey,
	i_blue,
	i_green,
	i_purple,
	i_red,
	i_grey
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


typedef struct s_hero
{
	unsigned char	program[CHAMP_MAX_SIZE];
	int32_t 		id;
	header_t		header;
	char 			*file_name;
}					t_hero;

typedef struct s_op
{
	char		name[6];
	char		arg_count;
	char		types[3];
	char		id;
	int 		cycles;
	char 		comment[40];
	t_bool		arg_type;
	t_bool 		carry;
	int 		dir_size;
	size_t		(*func)();
}				t_op;


typedef struct	s_cursor
{
	int32_t 	id;
	t_bool		carry;
	int32_t 	regs[REG_NUMBER];
	char 		op;
	int32_t 	live_cycle;
	int32_t 	cycles_to_die;
	size_t 		current;
	size_t 		step_to_next;
	t_color 	color;
	int			ready;

}				t_cursor;

typedef struct s_game
{
	void 		*arena;
	t_list		*cursor;
	int32_t		winner;
	int64_t 	total_cycles;
	int32_t 	check_live;
	int32_t 	cycles_to_die;
	int32_t 	checks_done;
	int32_t		player_count;
	int32_t		cursors_count;
	t_color		color[MEM_SIZE];

}				t_game;

typedef struct	s_data
{
	int			flags;
	t_hero		hero_list[MAX_PLAYERS];
}				t_data;

union u_types
{
	struct
	{
		unsigned ar3: 2;
		unsigned ar2: 2;
		unsigned ar1: 2;
		unsigned ar0: 2;
	};
	int32_t value;
};

size_t op_live(t_game *game, size_t current);
size_t ft_pass(t_game *game, size_t current);

static t_op	op_tab[17] =
	{
		{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 4, &op_live},
		{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, 4, &ft_pass},
		{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, 4, &ft_pass},
		{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, 4, &ft_pass},
		{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, 4, &ft_pass},
		{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, 4, &ft_pass},
		{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, 4, &ft_pass},
		{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, 4,&ft_pass},
		{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, 2,&ft_pass},
		{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, 2,&ft_pass},
		{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, 2,&ft_pass},
		{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, 2,&ft_pass},
		{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, 4,&ft_pass},
		{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, 2,&ft_pass},
		{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, 2,&ft_pass},
		{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, 4,&ft_pass},
		{"0", 0, {0}, 0, 0, "0", 0, 0, 0,&ft_pass}
	};


t_game *ft_init_game();
void ft_usage();

void ft_logo();
void *ft_game_over(t_game **game);


void ft_print_arena(t_game *game);
void ft_print_error(t_err err);
void ft_print_regs(t_game *game);
t_err ft_parse_input(int argc, char **argv, t_data **data);
t_err ft_parse_hero(t_hero *hero, t_mem *mem);
u_int64_t ft_atoin(void *data, size_t size);
void ft_past_heroes(t_game * game, t_data *data);
t_err ft_init_cursors(t_game *game);
t_cursor *ft_new_cursor();

void ft_battle(t_game *game);
void ft_print_result();
void ft_print_memory(void *start, void *end, void *mark, void *tail);
int ft_set_color(t_color color);
#endif
