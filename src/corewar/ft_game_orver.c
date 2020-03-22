#include "corewar.h"
#include "libft.h"

void *ft_game_over(t_game **game)
{
	if (!game || !(*game))
		return (NULL);
	if ((*game)->arena)
		ft_memdel((void**)&(*game)->arena);
	while((*game)->head)
	{
		(*game)->cursor = (*game)->head->next;
		ft_memdel((void**)&(*game)->head);
		(*game)->head = (*game)->cursor;
	}
	ft_memdel((void**)game);
	return (NULL);
}
