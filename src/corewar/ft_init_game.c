#include "corewar.h"
#include "libft.h"


t_game *ft_init_game()
{
	t_game *game;

	if (!(game = (t_game*)malloc(sizeof(*game))))
		return (NULL);
	if(!(game->arena = (void*)malloc(MEM_SIZE)))
	{
		ft_memdel((void**)game);
		return (NULL);
	}
	ft_bzero(game->arena, MEM_SIZE);
	game->cursor = NULL;
	return (game);
}