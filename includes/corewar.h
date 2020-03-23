//
// Created by xel on 13.03.2020.
//

#ifndef COREWAR_H
#define COREWAR_H

# include "op.h"
#include "libft.h"

# define OP_LEN 1
# define TYPE_LEN 1
# define REG_LEN 1
# define MAX_OP 16

typedef struct s_log
{
	int		fd_cursor;
	int 	fd_game;
	int		string_nbr;
	clock_t	start_time;
	clock_t current_time;
}		t_log;

typedef union u_vm{
	int64_t value;
	int32_t v_4;
	int16_t v_2;
	int8_t 	v_1;
}	t_vm;


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
	int32_t 		live;
	int32_t 		last_live;
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
	t_err		(*func)();
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
	size_t 		op_adr;
	size_t 		step_to_next;
	t_color 	color;
	t_bool 		alive;
	int32_t 	occupy;
	struct s_cursor *next;

}				t_cursor;


typedef struct s_game
{
	void		*arena;
	t_cursor 	*head;
	t_cursor 	*cursor;
	t_hero		*winner;
	int64_t 	total_cycles;
	int32_t 	check_live;
	int32_t 	cycle;
	int32_t 	cycles_to_die;
	int32_t 	checks_done;
	int32_t		player_count;
	int32_t		cursors_count;
	t_hero		*hero_list;
	t_color		color[MEM_SIZE];
	t_log		*log;

}				t_game;

typedef struct	s_data
{
	int32_t		dump;
	t_bool		enable_aff;
	t_hero		hero_list[MAX_PLAYERS];
}				t_data;

union u_types
{
	struct
	{
		unsigned char arg4: 2;
		unsigned char arg3: 2;
		unsigned char arg2: 2;
		unsigned char arg1: 2;
	};
	unsigned char value;
};

t_err op_live(t_game *game);
t_err ft_pass(t_game *game);
t_err op_ld(t_game *game);
t_err op_st(t_game *game);
t_err op_zjmp(t_game *game);
t_err op_sti(t_game *game);
t_err op_fork(t_game *game);
t_err op_add(t_game* game);
t_err op_sub(t_game* game);
t_err op_and(t_game* game);
t_err op_or(t_game* game);
t_err op_xor(t_game* game);
t_err op_ldi(t_game* game);
t_err op_lld(t_game *game);
t_err op_lldi(t_game* game);
t_err op_lfork(t_game *game);
t_err op_aff(t_game* game);

static t_op	op_tab[17] =
	{
		{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 4, &op_live},
		{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, 4, &op_ld},
		{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, 4, &op_st},
		{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, 4, &op_add},
		{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, 4, &op_sub},
		{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, 4, &op_and},
		{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, 4, &op_or},
		{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, 4,&op_xor},
		{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, 2, &op_zjmp},
		{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, 2,&op_ldi},
		{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, 2, &op_sti},
		{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, 2,&op_fork},
		{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, 4,&op_lld},
		{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, 2,&op_lldi},
		{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, 2,&op_lfork},
		{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, 4,&op_aff},
		{"0", 0, {0}, 0, 0, "0", 0, 0, 0,&ft_pass}
	};


t_game *ft_init_game();
void ft_usage();

void ft_logo();
void *ft_game_over(t_game **game);

void ft_itoa_vm(void *head, size_t address, u_int32_t value);
void ft_print_arena(t_game *game);
void ft_print_error(t_err err);
void ft_print_regs(t_game *game);
t_err ft_parse_input(int argc, char **argv, t_data **data);
t_err ft_parse_hero(t_hero *hero, t_mem *mem);
u_int32_t ft_atoin(void *data, size_t size);
void ft_past_heroes(t_game * game, t_data *data);
t_err ft_init_cursors(t_game *game);
t_cursor *ft_new_cursor();
t_err ft_clone_cursor(t_game *game, size_t address);
void ft_battle(t_game *game);
void ft_print_result(t_game *game);
void ft_print_memory(void *start, void *end, void *mark, void *tail);
int ft_set_color(t_color color);
//int32_t ft_atoi_vm(void* head, size_t *address, size_t size);
int32_t ft_get_data(t_game *game, int32_t arg_type);
/*
 * Logger
 */
t_vm ft_atoi_vm(void* head, size_t *address, size_t size);
void ft_log_game(t_game *game);
t_log *ft_logger_init(char *name);
void ft_log(t_log *log, char *string);
void ft_log_cursor(t_game *game, size_t prev);
void ft_print_memory_fd(int fd, void *start, void *end, void *mark, void *tail);
int32_t ft_convert_arg(int32_t arg, t_game *game, int32_t arg_type, t_bool idx);
int32_t ft_get_arg(t_game *game, int32_t arg_type, t_bool idx);
#endif
