#include "ft_printf.h"
#include "corewar.h"


int main(int argc, char **argv)
{
	t_game *game;

	ft_printf(CLR);
	if (!(game = ft_init_game()))
		return (0); //memory allocated error
//	*(int32_t*)(game->arena) = -1;
//	ft_print_arena(game->arena, MEM_SIZE);
	if (argc > 1 && argc < MAX_ARGS_NUMBER + 2)
	{

	}
	else if (argc == 1)
		ft_usage();
	else
		ft_print_error(1);
	ft_game_over(&game);
	return 0;
}
