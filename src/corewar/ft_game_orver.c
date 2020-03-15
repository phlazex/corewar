#include "corewar.h"
#include "libft.h"

void *ft_game_over(t_game **game)
{
	if (!game || !(*game))
		return (NULL);
	if ((*game)->arena)
		ft_memdel((void**)&(*game)->arena);
	while((*game)->cursor)
		ft_lstd_pop_front(&(*game)->cursor);
	ft_memdel((void**)game);
	return (NULL);
}
