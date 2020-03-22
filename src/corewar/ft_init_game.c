#include "corewar.h"
#include "libft.h"

static void ft_start_game(t_game *game)
{
	game->arena = NULL;
	game->head = NULL;
	game->cursor = NULL;
	game->winner = NULL;
	game->total_cycles = 0;

	game->check_live = 0;
	game->cycle = 0;
	game->cycles_to_die = CYCLE_TO_DIE;
	game->checks_done = 0;

	game->cursors_count = 0;
}

t_game *ft_init_game()
{
	t_game *game;

	if (!(game = (t_game*)malloc(sizeof(*game))))
		return (NULL);
	ft_start_game(game);
	if(!(game->arena = (void*)malloc(MEM_SIZE)))
		return (ft_game_over(&game));
	if(!(game->log = ft_logger_init(NULL)))
		return (ft_game_over(&game));
	ft_bzero(game->arena, MEM_SIZE);
	ft_bzero(game->color, MEM_SIZE * sizeof(t_color));

//	ft_bzero(fd_game->regs, sizeof(*(fd_game->regs)) * REG_NUMBER);
	return (game);
}