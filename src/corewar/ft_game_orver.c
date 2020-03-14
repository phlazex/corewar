#include "corewar.h"
#include "libft.h"

void ft_game_over(t_game **game)
{
	if (!game)
		return;
	ft_memdel((void**)&(*game)->arena);
	while((*game)->cursor)
		ft_lstd_pop_front(&(*game)->cursor);
	ft_memdel((void**)game);
}
