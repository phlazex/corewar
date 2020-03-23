#include "corewar.h"
#include "libft.h"

static void ft_start_game(t_game *game)
{
	game->cycles_to_die = CYCLE_TO_DIE;
}


t_game *ft_init_game()
{
	t_game *game;

	if (!(game = (t_game*)malloc(sizeof(*game))))
		return (NULL);
	ft_bzero(game, sizeof(*game));
	ft_start_game(game);
	if(!(game->arena = (void*)malloc(MEM_SIZE)))
		return (ft_game_over(&game));
	if(!(game->log = ft_logger_init(NULL)))
		return (ft_game_over(&game));
	ft_bzero(game->arena, MEM_SIZE);
	ft_bzero(game->color, MEM_SIZE * sizeof(t_color));
	return (game);
}