#include "corewar.h"
#include "libft.h"

static void ft_start_game(t_game *game)
{
	game->arena = NULL;
	game->cursor = NULL;
	game->winner = NULL;
	game->total_cycles = 0;
	game->check_live = 0;
	game->cycles_to_die = CYCLE_TO_DIE;
	game->checks_done = 0;
}

t_game *ft_init_game()
{
	t_game *game;

	if (!(game = (t_game*)malloc(sizeof(*game))))
		return (NULL);
	ft_start_game(game);
	if(!(game->arena = (void*)malloc(MEM_SIZE)))
		return (ft_game_over(&game));
	ft_bzero(game->arena, MEM_SIZE);
//	if(!(game->regs = (int32_t*)malloc(sizeof(*(game->regs)) * REG_NUMBER)))
//		return (ft_game_over(&game));
//	ft_bzero(game->regs, sizeof(*(game->regs)) * REG_NUMBER);
	return (game);
}