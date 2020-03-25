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
# define MAX_OPT 3

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
//	int32_t 		live;
//	int32_t 		last_live;
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
	size_t 		pc;
	size_t 		current;
	int32_t		op;
	int32_t 	id;
	int32_t 	occupy;
	t_bool		carry;
	int32_t 	regs[REG_NUMBER];
	t_bool 		alive;
	size_t		live_cycle;
	t_color 	color;

	struct s_cursor *next;

}				t_cursor;



typedef struct	s_data
{
	int32_t		dump;
	t_bool		quiet;
	t_bool		enable_aff;
	t_hero		hero_list[MAX_PLAYERS];
}				t_data;

typedef struct s_game
{
	void		*arena;
	t_cursor 	*head;
	t_cursor 	*cursor;
	t_hero		*winner;
	size_t 	total_cycles;
	int32_t 	check_live;
	int32_t 	cycle;
	int32_t 	cycles_to_die;
	int32_t 	checks_done;
	int32_t		player_count;
	int32_t		cursors_count;
	t_data		*input;
	t_color		color[MEM_SIZE];
	t_log		*log;
}				t_game;

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

typedef struct s_opt{
	uint8_t	id;
	char 	name[10];
	t_err	(*f)();
	unsigned int opt_arg;
	char 	arg_format[64];
	char	comment[512];
}				t_opt;

t_err ft_flag_q(int32_t argc, int32_t *current, char **argv, t_data *data);
t_err ft_flag_n(int32_t argc, int32_t *current, char **argv, t_data *data);
t_err ft_flag_dump(int32_t argc, int32_t *current, char **argv, t_data *data);
t_err ft_flag_a(int32_t argc, int32_t *current, char **argv, t_data *data);

static t_opt opt_tab[10] =
{
	{1,"-n", &ft_flag_n, 3,"[number]","Sets the number of the next player. If non-existent, the\n                    player will have the next available number in the order of\n                    the parameters. The last player will have the first process\n                    in the order of execution."},
	{2,"-q", &ft_flag_q, 0, "","Disable the display of each actual execution of the \"live\"\n                    instruction"},
	{3,"-dump", &ft_flag_dump, 2, "[nbr_cycles]","At the end of <nbr_cycles> of executions, dump the memory\n                    on the standard output and quit the game. The memory dumped\n                    in the hexadecimal format with 32 octets"
  "per line."},
	{4,"-a", &ft_flag_a, 0,"", "Enable aff function"}
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
t_bool ft_battle(t_game *game);
void ft_print_result(t_game *game);
void ft_print_memory(void *start, void *end, void *mark, void *tail);
int ft_set_color(t_color color);
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
t_err ft_is_correct_number(const char *number);
t_err ft_check_file_name(char *file_name);
#endif /* COREWAR_H */
